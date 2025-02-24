#include "../../includes/minishell.h"

char    **create_double_array(t_list *top, int input_len)
{
    t_list  *temp;
    char    **double_array;
    size_t  i;

    temp = NULL;
    i = 0;
    double_array = ft_calloc(input_len + 1, sizeof(char *));
    if (!double_array)
        exit (1);
    while (top)
    {
        temp = top;
        double_array[i] = ft_strdup(top->str);
        if (!double_array[i])
        {
            ft_free_double_array(double_array);
            exit (1);
        }
        top = top->next;
        ft_lstdelone(temp);
        i++;
    }
    double_array[i] = NULL;
    return (double_array);
}

//  Creates double array, inside red->filename, with the heredoc input
void    get_heredoc_input(t_token *token)
{
    char    *heredoc;
    int     input_len;
    t_list    *top;
    t_list    *input;

    input_len = 0;
    top = NULL;
    heredoc = NULL;
    while (1)
    {
        heredoc = readline("> ");
        if (!heredoc)
            exit (1);
        if (ft_strncmp(heredoc, token->red->filename[0], ft_strlen((const char*)heredoc)) == 0)
        {
            token->red->filename = create_double_array(top, input_len);
            return ;
        }
        input = ft_lstnew(heredoc);
        ft_lstadd_last(&top, input);
        input_len++;
    }
}
//  NOTE: PROTECT ALLOCATION ERRORS ^ -> return bool (false in case of error)

size_t  array_len(char **array)
{
    size_t  i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}

t_token    *get_heredoc_command_tree(t_token *token)
{
    while (token->previous && token->previous->red)
            token = token->previous;
    if (token->previous && token->previous->type == COMMAND)
        return (token->previous);
    return (NULL);
}

t_token    *get_heredoc_command_list(t_token *token)
{
    while (token->previous && token->previous->previous && token->previous->previous->red)
        token = token->previous->previous;
    if (token->previous && token->previous->type == COMMAND)
        return (token->previous);
    return (NULL);
}

//  Gives the extra file_input from heredoc to the command (creating a new double array)
void    get_redirection_files(t_token *token)
{
    t_token *command;
    char    **heredoc_file;
    char    **new_array;
    int     i;

    i = 0;
    command = get_heredoc_command_list(token);
    if (!command)
        return ;
    heredoc_file = token->red->filename + 1;
    new_array = ft_calloc(array_len(command->token) + array_len(heredoc_file) + 1, sizeof(char *));
    if (!new_array)
        return ;
    while (command->token[i])
    {
        new_array[i] = ft_strdup(command->token[i]);
        if (!new_array[i])
        {
            ft_free_double_array(new_array);
            return ;
        }
        i++;
    }
    while (*heredoc_file)
    {
        new_array[i] = ft_strdup(*heredoc_file);
        if (!new_array[i])
        {
            ft_free_double_array(new_array);
            return ;
        }
        i++;
        heredoc_file++;
    }
    new_array[i] = NULL;
    ft_free_double_array(command->token);
    command->token = new_array;
}

void    heredoc_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int     pipes[2];
    int     i;

    i = 0;
    if (!get_heredoc_command_tree(token))
        return ;
    if (token->red->fd == -1)
    {
        runcmd(token->previous, env, prompt_info);
        return ;
    }
    else
    {
        pipe(pipes);
        if (fork() == 0)
        {
            close(pipes[0]);
            while (token->red->filename[i])
            {
                ft_putstr_fd(token->red->filename[i], pipes[1]);
                ft_putstr_fd("\n", pipes[1]);
                i++;
            }
            exit(0);
        }
        wait(NULL);
        if (fork() == 0)
        {
            close(pipes[1]);
            dup2(pipes[0], STDIN_FILENO);
            close(pipes[0]);
            runcmd(token->previous, env, prompt_info);
            exit(0);
        }
        close(pipes[0]);
        close(pipes[1]);
        wait(NULL);
    }
}
