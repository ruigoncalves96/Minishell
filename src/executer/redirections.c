#include "../../includes/minishell.h"

int get_exit_status(int status)
{
    int signal_num;
    if (WIFEXITED(status)) {
        // Normal termination
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        // Terminated by signal
         signal_num = WTERMSIG(status);
        if (signal_num == SIGINT)  // Ctrl+C
            return 130;
        else if (signal_num == SIGQUIT)  // Ctrl+ barra
            return 131;
        else
            return 128 + signal_num;
    } else {
        return 1;
    }
}

//  PIPE.c

int  pipe_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int pipes[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int status;
    //  HANDLE POSSIBLE ERRORS PIPE / FORK
    if(pipe(pipes) == -1)
        return (perror("pipe"),-1);

    signal(SIGINT, SIG_IGN);
    left_pid = fork();
    if (left_pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        runcmd(token->previous, env, prompt_info);
        close_fds();
        cleanup_all(&prompt_info,token);
        exit(prompt_info.builtins->exit_code);
    }
    right_pid = fork();
    if (right_pid == 0)
    {
        dup2(pipes[0], STDIN_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        runcmd(token->next, env, prompt_info);
        close_fds();
        cleanup_all(&prompt_info,token);
        exit(prompt_info.builtins->exit_code);
    }
    close(pipes[0]);
    close(pipes[1]);
    waitpid(left_pid,&status,0);
    waitpid(right_pid,&status,0);
    set_signals();
    prompt_info.builtins->exit_code = get_exit_status(status);
    return (0);
}

//  REDIRECTIONS.c

static void    error_redirection_file(t_token *token, t_prompt_info prompt_info)
{
    if (token->red->fd == -1)
    {
        print_error(NULL,token->red->filename,ERROR_OPENING_FILE,true);
    }
    else if (token->red->fd == -2)
    {
        print_error(NULL,token->red->filename,PERMISSION_DENIED,true);
    }
    else if (token->red->fd == -3)
    {
        print_error(NULL,token->red->filename,NO_FILE_OR_DIRECTORY,true);
    }
    prompt_info.builtins->exit_code = 1;
}

void redirections_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    if (token->red->fd < 0 && token->red->fd != -4)
    {
        error_redirection_file(token, prompt_info);
        return ;
    }
    if ((token->red->type == OUT || token->red->type == A_OUT) && token->red->fd != -4)
    {
        if (dup2(token->red->fd, STDOUT_FILENO) == -1)
        {
            prompt_info.builtins->exit_code = 1;
            perror("dup2");
            close_fds();
            exit(1);
        }
        close(token->red->fd);  // Fechar FD após o dup2
        token->red->fd = -4;    // Marcar como fechado
    }
    else if (token->red->type == IN && token->red->fd != -4)
    {
        if (dup2(token->red->fd, STDIN_FILENO) == -1)
        {
            prompt_info.builtins->exit_code = 1;
            perror("dup2");
            close_fds();
            exit(1);
        }
        close(token->red->fd);  // Fechar FD após o dup2
        token->red->fd = -4;    // Marcar como fechado
    }
    if (token->previous && token->previous->type == COMMAND && (token->red->fd >= 0 || token->red->fd == -4))
        type_of_executer(token->previous, env, prompt_info);
    else if (token->previous && token->previous->type == OPERATOR)
        runcmd(token->previous, env, prompt_info);
}

// EXECUTER.c

void type_of_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int valid;

    if (token->token[0][0] == '\0' && token->subtype != T_QUOTE)
        return ;
    if (is_builtin(*token->token))
        execute_builtin(token, prompt_info, prompt_info.builtins);
    else
    {
        valid = validate_command_path(*token->token, env);
        if (valid == 0)
            executer_manager(token->token, env, prompt_info,token);
        else
            prompt_info.builtins->exit_code = valid;
    }
}

void runcmd(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    if (!token)
        return ;
    if (token->type == OPERATOR)
    {
        if (token->subtype == T_PIPE)
            pipe_executer(token, env, prompt_info);
        else if (token->subtype == T_REDIRECT)
        {
            if (token->red->type == HEREDOC)
                heredoc_executer(token, env, prompt_info);
            else
                redirections_executer(token, env, prompt_info);
        }
    }
    else if (token->type == COMMAND)
            type_of_executer(token, env, prompt_info);
}

void    loop_executer(t_token *token_head, t_env *env, t_prompt_info prompt_info)
{
    t_token *token;
    int original_fd[2];

    original_fd[0] = dup(STDIN_FILENO);
    original_fd[1] = dup(STDOUT_FILENO);
    if (original_fd[0] == -1 || original_fd[1] == -1)
    {
        if (original_fd[0] != -1)
            close(original_fd[0]);
        if (original_fd[1] != -1)
            close(original_fd[1]);
        return;
    }
    token = token_head;
    if (!token->next)
        type_of_executer(token, env, prompt_info);
    else
        runcmd(token, env, prompt_info);
    dup2(original_fd[0], STDIN_FILENO);
    dup2(original_fd[1], STDOUT_FILENO);
    close(original_fd[0]);
    close(original_fd[1]);
	if(prompt_info.builtins->exit_code % 128 == SIGINT && prompt_info.builtins->exit_code > 128)
		write(1, "\n", 1);
}

// EXECVE.c

static void handle_execve_error(char *path,char **env_array,t_prompt_info prompt_info,t_token *token)
{
    ft_free_double_array(env_array);
    if (access(path, F_OK) != 0)
    {
        free(path);
        perror("access");
        close_fds();
        prompt_info.builtins->exit_code = 127;
        exit(127);
    }
    if (access(path, X_OK) != 0)
    {
        free(path);
        perror("access");
        close_fds();
        prompt_info.builtins->exit_code = 126;
        exit(126);
    }
    free(path);
    perror("execve");
    cleanup_all(&prompt_info,token);
    exit(1);
}

int executer_manager(char **str, t_env *env,t_prompt_info prompt_info,t_token *token)
{
	char *path;
	char **env_array;
	pid_t child;
	int status;

    path = get_command_path(*str,env);
    env_array = convert_env_to_array(env);
    if(!path)
    {
        prompt_info.builtins->exit_code = 127;
        if (env_array)
            ft_free_double_array(env_array);
        return 1;
    }
    child = fork();
    if(child == 0)
    {
   	    signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if(execve(path,str,env_array) == -1)
            handle_execve_error(path,env_array,prompt_info,token);
    }
    signal(SIGINT, SIG_IGN);
    waitpid(child,&status, 0);
    prompt_info.builtins->exit_code = get_exit_status(status);
    set_signals();
    free(path);
    if (env_array)
        ft_free_double_array(env_array);
    return 0;
}
