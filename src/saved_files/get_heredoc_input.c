#include "../../includes/minishell.h"

static char    **create_double_array(t_list *top, size_t input_len)
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

static char	*expand_vars_heredoc(char *heredoc, t_prompt_info prompt_info)
{
	char   *var_value;
	char   *dollar;

	var_value = NULL;
	while (1)
	{
        dollar = heredoc;
        dollar += ft_strlen(var_value);
	    dollar = ft_strchr(dollar, '$');
		if (!dollar)
			break ;
		var_value = find_var_value(prompt_info, dollar);
		heredoc = join_var(heredoc, var_value, dollar);
		if (!heredoc)
			return (NULL);
	}
	return (heredoc);
}

static void heredoc_readline(char *heredoc, t_token *token, t_prompt_info *prompt_info, int pipefd)
{
    while (1)
    {
        heredoc= readline("> ");
        if (!heredoc || heredoc_c_pressed)
        {
            if(heredoc_c_pressed)
            {
                cleanup_all(prompt_info, NULL);
                free_token_list(token);
                close(pipefd);
                prompt_info->builtins->exit_code = 130;
                exit(prompt_info->builtins->exit_code);
            }
            else
            {
                print_error("minishell", NULL, EOF_WARNING, 0);
                break ;
            }
        }
        if (ft_strcmp(heredoc, token->red->filename) == 0)
        {
            free(heredoc);
            break ;
        }
        if (token->next->subtype != T_QUOTE && token->next->token[1] == NULL)
            heredoc = expand_vars_heredoc(heredoc, *prompt_info);
        ft_putstr_fd(heredoc, pipefd);
        ft_putstr_fd("\n", pipefd);
        free(heredoc);
    }
}

static bool get_heredoc_to_array(t_token *token, int pipefd)
{
    char    *new_line;
    t_list  *list;
    t_list  *list_node;

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
        {
            free(new_line);
            free_list(list);
            return (false);
        }
        ft_lstadd_last(&list, list_node);
    }
    close(pipefd);
    token->red->heredoc = create_double_array(list, lst_size(list));
    free_list(list);
    if (!token->red->heredoc)
        return (false);
    return (true);
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

static void clean_child(t_token *token, t_prompt_info *prompt_info, int exit_code)
{
    free_token_list(token);
    cleanup_all(prompt_info, NULL);
    exit(exit_code);
}

//  Creates double array, inside red->filename, with the heredoc input
bool get_heredoc_input(t_token *token, t_prompt_info prompt_info)
{
    int pipefd[2];
    pid_t pid;
    char    *heredoc;
    int     status;

    heredoc = NULL;
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
        heredoc_readline(heredoc, token, &prompt_info, pipefd[1]);
        close(pipefd[1]);
        if(heredoc_c_pressed)
            clean_child(token, &prompt_info, 130);
        clean_child(token, &prompt_info, 0);
    }
    close(pipefd[1]);
    waitpid(pid,&status, 0);
    set_signals();
    if (check_heredoc_exit(status, pipefd[0], prompt_info) == false)
        return (false);
    if (get_heredoc_to_array(token, pipefd[0]) == false)
        return (false);
    return (true);
}
