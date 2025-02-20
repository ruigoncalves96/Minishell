#include "../../includes/minishell.h"
#include <unistd.h>

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

size_t  array_len(char **array)
{
    size_t  i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}

void    get_heredoc_files(t_token *token)
{
    char    **command;
    char    **heredoc;
    char    **new_array;
    int     i;

    i = 0;
    command = token->previous->token;
    heredoc = token->red->filename + 1;
    new_array = ft_calloc(array_len(command) + array_len(heredoc) + 1, sizeof(char *));
    if (!new_array)
        return ;
    while (*command)
    {
        new_array[i] = ft_strdup(*command);
        if (!new_array[i])
        {
            ft_free_double_array(new_array);
            return ;
        }
        i++;
        command++;
    }
    while (*heredoc)
    {
        new_array[i] = ft_strdup(*heredoc);
        if (!new_array[i])
        {
            ft_free_double_array(new_array);
            return ;
        }
        i++;
        heredoc++;
    }
    new_array[i] = NULL;
    ft_free_double_array(token->previous->token);
    token->previous->token = new_array;
}

void    heredoc_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int     pipes[2];
    int     i;

    i = 0;
    if (token->red->fd == -1 /*|| token->red->filename[1] == NULL*/)
    {
        runcmd(token->previous, env, prompt_info);
        return ;
    }
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
