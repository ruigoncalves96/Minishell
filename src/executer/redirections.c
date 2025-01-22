#include "../../includes/minishell.h"

static int open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return 1;
    //[X] abrir o arquivo
   // printf("Redirect filename: %s\n", token->red->filename[0]);
    if(token->red->type == OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if(token->red->type == A_OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if(token->red->type == IN)
        token->red->fd = open(token->red->filename[0], O_RDONLY);
    if(token->red->fd == -1)
    {
        //Talvez tenha de dar free no red e na str
        return 1;
    }
    return 0;
}

static void loop_and_open_fd(t_token *token)
{
    while (token)
    {
        if(token->next && token->next->subtype == T_REDIRECT)
        {
              if(open_redirect(token->next) == 1)
                    printf("Aconteceu alguma coisa de errado equanto processo de escrever o namefile\n");
        }
        token = token->next;
    }
}

static void handle_redirections(t_token *token)
{
    if (token->red->type == OUT || token->red->type == A_OUT)
    {
        if (dup2(token->red->fd, STDOUT_FILENO) == -1)
            return (perror("dup2"));
    }
    else if (token->red->type == IN)
    {
        if (dup2(token->red->fd, STDIN_FILENO) == -1)
            return (perror("dup2"));
    }
    close(token->red->fd);  // Fechar FD após o dup2
    token->red->fd = -1;    // Marcar como fechado
    token = token->next;
}

static void close_stuff( int *backup_fd)
{
    dup2(backup_fd[0], STDIN_FILENO);
    dup2(backup_fd[1], STDOUT_FILENO);
    close(backup_fd[0]);
    close(backup_fd[1]);
}

static void type_of_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    if(is_builtin(*token->token))
        execute_builtin(token,prompt_info);
    else if(validate_command_path(*token->token,env) == 0)
        executer_manager(token->token,env);
}

static int  pipe_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int pipes[2];
    int child;

    pipe(pipes);
    child = fork();
    if (child == 0)
    {
        close(pipes[0]);
        dup2(pipes[1], STDOUT_FILENO);
        type_of_executer(token->previous, env, prompt_info);
        close(pipes[1]);
        exit (0);
    }
    else
    {
        close(pipes[1]);
        dup2(pipes[0], STDIN_FILENO);
        wait(NULL);
        type_of_executer(token->next, env, prompt_info);
        close(pipes[0]);
    }
    return (0);
}

//[X]Primeiro loop para abrir as coisas
//[] Loop para verificar comandos
void loop_executer(t_token *token,t_env *env,t_prompt_info prompt_info)
{
    int original_fd[2];

    original_fd[0] = dup(STDIN_FILENO);
    original_fd[1] = dup(STDOUT_FILENO);
    loop_and_open_fd(token);
    if (!token->next)
        type_of_executer(token, env, prompt_info);
    else
    {
        while (token)
        {
            if(token->type == OPERATOR)
            {
                if(token->subtype == T_PIPE)
                    pipe_executer(token, env, prompt_info);
                else if (token->subtype == T_REDIRECT)
                    handle_redirections(token->next);
                close_stuff(original_fd);
            }
            token = token->next;
        }
    }
}

int executer_manager( char **str,t_env *env)
{
	char *path;
	char **env_array;
	int child;

    child = fork();
    env_array = convert_env_to_array(env);
	path = get_command_path(*str,env);
	if(!path)
        return (ft_free_double_array(env_array), -1);
    if(child == 0)
    {
        if(execve(path,str,env_array) == -1)
        {
            perror("exeve");
            free(path);
            ft_free_double_array(env_array);
        }
    }
    else
    {
        wait(NULL);
        free(path);
    }
    ft_free_double_array(env_array);
    return 0;
}
