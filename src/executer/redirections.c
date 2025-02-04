#include "../../includes/minishell.h"

static int open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return 1;
    //[X] abrir o arquivo
   // printf("Redirect filename: %s\n", token->red->filename[0]);
    // Close previous fd if it's still open
    if (token->red->fd != -1)
    {
        close(token->red->fd);
        token->red->fd = -1;
    }

    if(token->red->type == OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if(token->red->type == A_OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if(token->red->type == IN)
        token->red->fd = open(token->red->filename[0], O_RDONLY);
    if(token->red->fd == -1)
    {
        return 1;
    }
    return 0;
}
//

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

static bool handle_redirections(t_token *token, int *backup_fd)
{

    if (!token->next || token->next->subtype != T_REDIRECT)
        return false;

    backup_fd[0] = dup(STDIN_FILENO);
    backup_fd[1] = dup(STDOUT_FILENO);

    while (token->next && token->next->subtype == T_REDIRECT)
    {
        if (token->next->red->type == OUT || token->next->red->type == A_OUT)
        {
            if (dup2(token->next->red->fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                return false;
            }
        }
        else if (token->next->red->type == IN)
        {
            if (dup2(token->next->red->fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                return false;
            }
        }
        close(token->next->red->fd);
        token->next->red->fd = -1;
        token = token->next->next;
        if(!token)
            break;
    }
    return true;
}
static void close_stuff( int *backup_fd)
{
    dup2(backup_fd[0], STDIN_FILENO);
    dup2(backup_fd[1], STDOUT_FILENO);
    close(backup_fd[0]);
    close(backup_fd[1]);
}

void loop_executer(t_token *token,t_env *env,t_prompt_info prompt_info)
{
    int original_fd[2];
    bool redir_done;
    loop_and_open_fd(token);
    while (token)
    {
        if(token->type == COMMAND)
        {
            if(token->next && token->next->type == T_PIPE)
            {
                printf("vem ai o monstro aiai\n");
            }else
            {
                redir_done =   handle_redirections(token,original_fd);
                if(is_builtin(*token->token))
                {
                    execute_builtin(token,prompt_info);
                }
                else if(validate_command_path(*token->token,env) == 0)
                {
                    executer_manager(token->token,env);
                }
                if (redir_done)
                    close_stuff(original_fd);
            }
        }
        token = token->next;
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
        {
            ft_free_double_array(env_array);
            return -1;
        }
        if(child == 0)
        {
            if(execve(path,str,env_array) == -1)
            {
             perror("exeve");
             free(path);
             ft_free_double_array(env_array);
             exit(1);
            }
        }else
        {
            wait(NULL);
            free(path);
        }
            ft_free_double_array(env_array);
    return 0;
}
