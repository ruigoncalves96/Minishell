#include "../../includes/minishell.h"

static int open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return 1;

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
        ft_putstr_fd("Error opening file: ", 2);
        ft_putstr_fd(token->red->filename[0], 2);
        ft_putstr_fd("\n", 2);
        // -2 significa que o token deu erro exemplo nao tem permissoes
        token->red->fd = -2;
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
              open_redirect(token->next);
        }
        token = token->next;
    }

}

static t_token *handle_redirections(t_token *token, int *backup_fd)
{

    if(!token)
        return NULL;

    if (!token->next || token->next->subtype != T_REDIRECT)
        return token->next;

    backup_fd[0] = dup(STDIN_FILENO);
    backup_fd[1] = dup(STDOUT_FILENO);

    while (token->next && token->next->subtype == T_REDIRECT)
    {
        if(token->next->red->fd == -2)
                return (t_token *)-1;
        if (token->next->red->type == OUT || token->next->red->type == A_OUT)
        {
            if (dup2(token->next->red->fd, STDOUT_FILENO) == -1)
            {
                token = token->next;
                break;
            }
        }
        else if (token->next->red->type == IN)
        {
            if (dup2(token->next->red->fd, STDIN_FILENO) == -1)
            {
                token = token->next;
                break;
            }
        }
        close(token->next->red->fd);
        token->next->red->fd = -1;
        token = token->next->next;
    }
    if(token)
        return token->next;
    else
        return NULL;
}
static void close_stuff( int *backup_fd)
{
    dup2(backup_fd[0], STDIN_FILENO);
    dup2(backup_fd[1], STDOUT_FILENO);
    close(backup_fd[0]);
    close(backup_fd[1]);
}


void loop_executer(t_token *token, t_env *env, t_prompt_info prompt_info, t_builtins *builtins)
{
    int original_fd[2];
    t_token *current_cmd;
    t_token *redir_result;
    loop_and_open_fd(token);

    while (token)
    {
        if (token->type == COMMAND)
        {
            if (token->next && token->next->type == T_PIPE)
            {
                printf("vem ai o monstro aiai\n");
            }
            else
            {
                current_cmd = token;
                redir_result = handle_redirections(token, original_fd);
                // Se handle_redirections retornou -1, houve erro no redirecionamento.
                if (redir_result == (t_token *)-1)
                {
                    close_stuff(original_fd);
                    token = token->next;  // Pula este comando sem executá-lo.
                    continue;
                }
                token = redir_result;

                if (is_builtin(*current_cmd->token))
                {
                    execute_builtin(current_cmd, prompt_info, builtins);
                }
                else if (validate_command_path(*current_cmd->token, env) == 0)
                {
                    executer_manager(current_cmd->token, env);
                }
                close_stuff(original_fd);
            }
        }
        else
        {
            token = token->next; // Ignora tokens de redirecionamento ou outros
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
