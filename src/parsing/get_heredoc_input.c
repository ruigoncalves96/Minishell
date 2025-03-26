#include "../../includes/minishell.h"

static char **create_double_array(t_list *top, size_t input_len)
{
    char    **double_array;
    size_t  i;

    i = 0;
    double_array = ft_calloc(input_len + 1, sizeof(char *));
    if (!double_array)
        return (NULL);
    while (top)
    {
        if (top->str[0] == '\0')
            double_array[i] = ft_strdup("\n");
        else
            double_array[i] = ft_strdup(top->str);
        if (!double_array[i])
        {
            ft_free_double_array(double_array);
            return (NULL);
        }
        top = top->next;
        i++;
    }
    double_array[i] = NULL;
    return (double_array);
}

static bool check_heredoc_exit(int status, int pipefd, t_prompt_info prompt_info)
{
    if (get_exit_status(status) == 130)
    {
        prompt_info.builtins->exit_code = get_exit_status(status);
        write(1, "\n", 1);
        close(pipefd);
        return (false);
    }
    return (true);
}

static bool save_heredoc_input(t_token *token, int pipefd)
{
    t_list  *list;
    t_list  *list_node;
    char    *new_line;

    list = NULL;
    list_node = NULL;
    new_line = NULL;
    while (1)
    {
        new_line = get_next_line(pipefd);
        if (!new_line)
            break ;
        list_node = ft_lstnew(new_line);
        if (!list_node)
            return (free(new_line), free_list(list), false);
        ft_lstadd_last(&list, list_node);
    }
    close(pipefd);
    token->red->heredoc = create_double_array(list, lst_size(list));
    if (!token->red->heredoc)
        return (free_list(list), false);
    free_list(list);
    return (true);
}

//  Creates double array, inside red->filename, with the heredoc input
bool get_heredoc_input(t_token *token, t_prompt_info prompt_info)
{
    int pipefd[2];
    pid_t pid;
    int     status;

    signal(SIGINT,SIG_IGN);
    if (pipe(pipefd) == -1)
         return (perror("pipe"), false);
    pid = fork();
    if (pid == -1)
         return (perror("fork"), false);
    if (pid == 0)
    {
        heredoc_c_pressed = 0;
        signal(SIGINT, handler_heredoc);
        close(pipefd[0]);
        readline_heredoc(token, &prompt_info, pipefd[1]);
    }
    close(pipefd[1]);
    waitpid(pid,&status, 0);
    set_signals();
    if (check_heredoc_exit(status, pipefd[0], prompt_info) == false)
        return (false);
    if (save_heredoc_input(token, pipefd[0]) == false)
        return (false);
    return (true);
}
