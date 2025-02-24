#include "../../includes/minishell.h"

static void type_of_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int valid;

    if (token->token[0][0] == '\0')
        return ;
    if (is_builtin(*token->token))
        execute_builtin(token, prompt_info, prompt_info.builtins);
    else
    {
        valid = validate_command_path(*token->token, env);
        if (valid == 0)
            executer_manager(token->token, env, prompt_info);
        else
            prompt_info.builtins->exit_code = valid;
    }
}

static int  pipe_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
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
        exit(prompt_info.builtins->exit_code);
    }
    close(pipes[0]);
    close(pipes[1]);
    waitpid(left_pid,NULL,0);
    waitpid(right_pid,&status,0);
    set_signals();
    prompt_info.builtins->exit_code = (status >> 8) & 0xFF;
    return (0);
}

static void redirections_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    if ((token->red->type == OUT || token->red->type == A_OUT) && token->red->fd != -1)
    {
        if (dup2(token->red->fd, STDOUT_FILENO) == -1)
        {
            prompt_info.builtins->exit_code = 1;
            perror("dup2");
            exit(1);  
        }
        close(token->red->fd);  // Fechar FD após o dup2
        token->red->fd = -1;    // Marcar como fechado
    }
    else if (token->red->type == IN && token->red->fd != -1)
    {
        if (dup2(token->red->fd, STDIN_FILENO) == -1)
        {
            prompt_info.builtins->exit_code = 1;
            perror("dup2");
            exit(1);  
        }
        close(token->red->fd);  // Fechar FD após o dup2
        token->red->fd = -1;    // Marcar como fechado
    }
    if (token->previous && token->previous->type == COMMAND)
        type_of_executer(token->previous, env, prompt_info);
    else if (token->previous && token->previous->type == OPERATOR)
        runcmd(token->previous, env, prompt_info);
}

void runcmd(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    if (token->type == OPERATOR)
    {
        if (token->subtype == T_PIPE)
            pipe_executer(token, env, prompt_info);
        else if (token->subtype == T_REDIRECT)
        {
            if (token->red->type != HEREDOC)
                redirections_executer(token, env, prompt_info);
            else
                heredoc_executer(token, env, prompt_info);
        }
    }
    else if (token->type == COMMAND)
            type_of_executer(token, env, prompt_info);
}

//[X]Primeiro loop para abrir as coisas
//[X] Loop para verificar comandos
void    loop_executer(t_token *token_head, t_env *env, t_prompt_info prompt_info)
{
    t_token *token;
    int original_fd[2];

    original_fd[0] = -1;
    original_fd[1] = -1;
    original_fd[0] = dup(STDIN_FILENO);
    original_fd[1] = dup(STDOUT_FILENO);
    token = token_head;
    if (!token->next)
        type_of_executer(token, env, prompt_info);
    else
        runcmd(token, env, prompt_info);
    if (STDIN_FILENO != original_fd[0])
        dup2(original_fd[0], STDIN_FILENO);
    if (STDOUT_FILENO != original_fd[1])
        dup2(original_fd[1], STDOUT_FILENO);
    // close(original_fd[0]);
    // close(original_fd[1]);
}
static void exit_code_child(t_prompt_info prompt_info)
{
    int status;
    int exit_code;

    wait(&status);
    exit_code = (status >> 8) & 0xFF;
    prompt_info.builtins->exit_code = exit_code;
    
}

static void handle_execve_error(char *path,char **env_array,t_prompt_info prompt_info)
{
    ft_free_double_array(env_array);

    //arquivo existe
    if (access(path, F_OK) != 0)
    {
        free(path);
        perror("access");
        prompt_info.builtins->exit_code = 127;
        exit(127);
    }
    // arquivo existe mas nao tem permisao de execucao
    if (access(path, X_OK) != 0)
    {
        free(path);
        perror("access");
        prompt_info.builtins->exit_code = 126;
        exit(126);
    }
    free(path);
    perror("execve");
    exit(1);
}

int executer_manager(char **str, t_env *env,t_prompt_info prompt_info)
{
	char *path;
	char **env_array;
	pid_t child;
    
    path = get_command_path(*str,env);
    env_array = convert_env_to_array(env);
    if(!path)
    {
        prompt_info.builtins->exit_code = 127;
         ft_free_double_array(env_array);
    }
    child = fork();
 
    // signal(SIGINT, SIG_IGN);
    if(child == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        if(execve(path,str,env_array) == -1)
            handle_execve_error(path,env_array,prompt_info);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        exit_code_child(prompt_info);
        set_signals();
    }
    free(path);
    // set_signals();
    ft_free_double_array(env_array);
    return 0;
}
