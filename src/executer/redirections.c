#include "../../includes/minishell.h"

static int open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return 1;
    // [X] abrir o arquivo
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

static void find_and_delete(t_token *node, t_token **new_token_list)
{
    t_token *delete;
    t_token *last;

    delete = NULL;
    last = node;
    while (last->next->next && last->next->next->subtype == T_REDIRECT
        && (last->red->type == OUT || last->red->type == A_OUT))
        last = last->next->next;
    if (last != node)
    {
        while (node != last)
        {
            delete = node;
            if (node->previous == NULL)
                *new_token_list = node->next;
            node = node->next;
            ft_token_delone(delete);
        }
    }
}

static void parse_redirect_out(t_token **token)
{
    t_token *new_token_list;
    t_token *node;

    new_token_list = NULL;
    node = *token;
    while (node)
    {
        if (node->subtype == T_REDIRECT && (node->red->type == OUT || node->red->type == A_OUT))
            find_and_delete(node, &new_token_list);
        node = node->next;
    }
    if (new_token_list)
        *token = new_token_list;
}

// static void close_stuff( int *backup_fd)
// {
//     dup2(backup_fd[0], STDIN_FILENO);
//     dup2(backup_fd[1], STDOUT_FILENO);
//     close(backup_fd[0]);
//     close(backup_fd[1]);
// }

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
        close(pipes[1]);
        // return (0); //
        type_of_executer(token->previous, env, prompt_info);
        exit(0);
    }
    else
    {
        close(pipes[1]);
        dup2(pipes[0], STDIN_FILENO);
        close(pipes[0]);
        wait(NULL);
        // child = fork(); //
        // if (child == 0) //
        //     return (0); //
        // else            //
        //     wait(NULL); //
         type_of_executer(token->next, env, prompt_info);
    }
    return (0);
}

static void redirections_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
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
    if (token->previous)
        type_of_executer(token->previous, env, prompt_info);
}

//  Find last pipe and return it
//  Find last > / >> and return it
//  Find next < and return it
//
// static t_token *find_pipe(t_token *token)
// {
//     t_token *pipe;

//     pipe = NULL;
//     while (token)
//     {
//         if (token->subtype == T_PIPE)
//             pipe = token;
//         token = token->next;
//     }
//     return (pipe);
// }

// static t_token *find_redirect(t_token *token, int type)
// {
//     while (token)
//     {
//         if (token->subtype == T_REDIRECT)
//         {
//             if (type == IN && token->red->type == type)
//                 return (token);
//             else if ((type == OUT) && (token->red->type == OUT || token->red->type == A_OUT))
//                 return (token);
//         }
//         token = token->next;
//     }
//     return (NULL);
// }

// static void find_executer(t_token *token)
// {
//     find_pipe(token);
//     find_redirect(token, OUT);
//     find_redirect(token, IN);
// }

//[X]Primeiro loop para abrir as coisas
//[] Loop para verificar comandos
void    loop_executer(t_token **token_head, t_env *env, t_prompt_info prompt_info)
{
    t_token *token;
    int original_fd[2];

    original_fd[0] = dup(STDIN_FILENO);
    original_fd[1] = dup(STDOUT_FILENO);
    loop_and_open_fd(*token_head);
    parse_redirect_out(token_head);
    token = *token_head;
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
                    redirections_executer(token, env, prompt_info);
                dup2(original_fd[0], STDIN_FILENO);
                dup2(original_fd[1], STDOUT_FILENO);
            }
            token = token->next;
        }
    }
    close(original_fd[0]);
    close(original_fd[1]);
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
	signal(SIGINT, SIG_IGN);
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
    else
    {
        wait(NULL);
        free(path);
    }
    set_signals();
    ft_free_double_array(env_array);
    return 0;
}
