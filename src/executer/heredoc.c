#include "../../includes/minishell.h"

char    **create_double_array(t_list *top, size_t input_len)
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

char	*expand_vars_heredoc(char *heredoc, t_prompt_info prompt_info)
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
		heredoc = join_var(heredoc, var_value, dollar, var_key_len(dollar + 1));
		if (!heredoc)
			return (NULL);
	}
	return (heredoc);
}

size_t lst_size(t_list *list)
{
    size_t i;

    i = 0;
    while (list)
    {
        i++;
        list = list->next;
    }
    return i;
}


//  Creates double array, inside red->filename, with the heredoc input
bool get_heredoc_input(t_token *token, t_prompt_info prompt_info)
{
    int pipefd[2];
    pid_t pid;
    char    *heredoc;
    char    *new_line;
    int     status;
    t_list  *list;

    list = NULL;
    new_line = NULL;
    heredoc = NULL;
    signal(SIGINT,SIG_IGN);
    if (pipe(pipefd) == -1)
    {
         perror("pipe");
         return (false);
    }
    pid = fork();
    if (pid == -1) {
         perror("fork");
         return (false);
    }
    if (pid == 0)
     {
        heredoc_c_pressed = 0;
        signal(SIGINT, handler_heredoc);

         close(pipefd[0]);
         while (1)
         {
            heredoc= readline("> ");
            if (!heredoc || heredoc_c_pressed)
            {
                if(heredoc_c_pressed)
                {
                    cleanup_all(&prompt_info, NULL);
                    free_token_list(token);
                    close(pipefd[1]);
                    prompt_info.builtins->exit_code = 130;
                    exit(prompt_info.builtins->exit_code);
                }else
                {
                    print_error("minishell", NULL,
                        "warning: here-document delimited by end-of-file (wanted `EOF')", 0);
                    break ;
                }
            }
            // Terminate on the expected delimiter
            if (ft_strcmp(heredoc, token->red->filename) == 0)
                break ;
            if (token->next->subtype != T_QUOTE && token->next->token[1] == NULL)
                heredoc = expand_vars_heredoc(heredoc, prompt_info);
            ft_putstr_fd(heredoc, pipefd[1]);
            ft_putstr_fd("\n", pipefd[1]);
            free(heredoc);
         }
         if (heredoc)
            free(heredoc);
         close(pipefd[1]);
         if(heredoc_c_pressed)
         {
            free_token_list(token);
            cleanup_all(&prompt_info, NULL);
            exit(130);
         }
         free_token_list(token);
         cleanup_all(&prompt_info, NULL);
         exit(EXIT_SUCCESS);
    }
    close(pipefd[1]);
    waitpid(pid,&status, 0);
    //signal(SIGINT,SIG_IGN);
    set_signals();
    if (get_exit_status(status) == 130) //|| (IFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        prompt_info.builtins->exit_code = get_exit_status(status);
        write(1, "\n", 1);
        close(pipefd[0]);
        return (false);
    }
    while (1)
    {
        new_line = get_next_line(pipefd[0]);
        if (!new_line)
            break;
        ft_lstadd_last(&list, ft_lstnew(new_line));
    }
    close(pipefd[0]);
    token->red->heredoc = create_double_array(list, lst_size(list));
    free_list(list);
    return (true);
}

size_t  array_len(char **array)
{
    size_t  i;

    i = 0;
    if (!array)
        return (0);
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

void    get_redirection_files(t_token *token)
{
    t_token *command;
    char    **red_command;
    char    **new_array;
    int     i;

    i = 0;
    command = get_heredoc_command_list(token);
    if (!command)
        return ;
    red_command = token->next->token + 1;
    new_array = ft_calloc(array_len(command->token) + array_len(red_command) + 1, sizeof(char *));
    if (!new_array)
        return ;
    while (command->token && command->token[i])
    {
        new_array[i] = ft_strdup(command->token[i]);
        if (!new_array[i])
        {
            ft_free_double_array(new_array);
            return ;
        }
        i++;
    }
    while (*red_command)
    {
        new_array[i] = ft_strdup(*red_command);
        if (!new_array[i])
        {
            ft_free_double_array(new_array);
            return ;
        }
        i++;
        red_command++;
    }
    new_array[i] = NULL;
    if (command->token)
        ft_free_double_array(command->token);
    command->token = new_array;
}

void    heredoc_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int     pipes[2];
    int     i;

    i = 0;
    if (token->red->fd == -4 || !get_heredoc_command_tree(token))
        runcmd(token->previous, env, prompt_info);
    else
    {
        if (pipe(pipes) == -1)
            return;
        if (fork() == 0)
        {
            close(pipes[0]);
            while (token->red->heredoc[i])
            {
                ft_putstr_fd(token->red->heredoc[i], pipes[1]);
                i++;
            }
            cleanup_all(&prompt_info,token);
            exit(0);
        }
        int status;

        wait(&status);
        if (fork() == 0)
        {
            close(pipes[1]);
            dup2(pipes[0], STDIN_FILENO);
            close(pipes[0]);
            runcmd(token->previous, env, prompt_info);
            cleanup_all(&prompt_info,token);
            exit(0);
        }
        close(pipes[0]);
        close(pipes[1]);
        wait(&status);
        prompt_info.builtins->exit_code = get_exit_status(status);
    }
}
