#include "../../includes/minishell.h"

static void type_of_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    if(is_builtin(*token->token))
        execute_builtin(token,prompt_info, prompt_info.builtins);
    else if(validate_command_path(*token->token,env) == 0)
        executer_manager(token->token,env);
}

static int  pipe_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int pipes[2];

    //  HANDLE POSSIBLE ERRORS PIPE / FORK
    pipe(pipes);
    if (fork() == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        runcmd(token->previous, env, prompt_info);
        exit(0);
    }
    if (fork() == 0)
    {
        dup2(pipes[0], STDIN_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        runcmd(token->next, env, prompt_info);
        exit(0);
    }
    close(pipes[0]);
    close(pipes[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}

static void redirections_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    if ((token->red->type == OUT || token->red->type == A_OUT) && token->red->fd != -1)
    {
        if (dup2(token->red->fd, STDOUT_FILENO) == -1)
            return (perror("dup2"));
        close(token->red->fd);  // Fechar FD após o dup2
        token->red->fd = -1;    // Marcar como fechado
    }
    else if (token->red->type == IN && token->red->fd != -1)
    {
        if (dup2(token->red->fd, STDIN_FILENO) == -1)
            return (perror("dup2"));
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
//[] Loop para verificar comandos
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

int executer_manager(char **str, t_env *env)
{
	char *path;
	char **env_array;
	int child;

    child = fork();
    env_array = convert_env_to_array(env);
	path = get_command_path(*str,env);
	if(!path)
        return (ft_free_double_array(env_array), -1);
	// signal(SIGINT, SIG_IGN);
    if(child == 0)
    {
        if(execve(path,str,env_array) == -1)
        {
            perror("exeve");
            free(path);
            ft_free_double_array(env_array);
            exit (1);
        }
        exit (0);
    }
    wait(NULL);
    free(path);
    // set_signals();
    ft_free_double_array(env_array);
    return 0;
}
