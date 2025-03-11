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
		heredoc = join_var(heredoc, var_value, dollar, var_key_len(dollar + 1));
		if (!heredoc)
			return (NULL);
	}
	return (heredoc);
}

static size_t lst_size(t_list *list)
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
void get_heredoc_input(t_token *token, t_prompt_info prompt_info)
{
    char *heredoc;
    char *tmp;
    t_list *top;
    t_list *input;
    (void)prompt_info;

    top = NULL;
    input = NULL;
   signal(SIGINT,SIG_IGN);
    pid_t child = fork();

    if(child == 0)
    {
        signal(SIGINT,SIG_DFL);
        while (1)
        {

            heredoc = readline("> ");

            // Check for Ctrl+D (EOF)
            if (heredoc == NULL)
            {
                print_error(NULL, NULL, "warning: here-document delimited by end-of-file (wanted `EOF')", true);
                prompt_info.builtins->exit_code = 0;

                //funciona bem
                 if(token->red->filename)
                    ft_free_double_array(token->red->filename);

                if(heredoc)
                {
                    free(heredoc);
                }
                cleanup_all(&prompt_info,NULL);
                exit(0);
                }

                // Check for delimiter
                if (ft_strcmp(heredoc, token->red->filename[0]) == 0)
                {
                    free(heredoc);
                    if (top)
                    {
                        free_list(top);
                    }
                    cleanup_all(&prompt_info,NULL);
                exit(0);
            }

            // Process and add the line
            if (token->next->subtype != T_QUOTE && token->red->filename[1] == NULL)
            heredoc = expand_vars_heredoc(heredoc, prompt_info);

            tmp = ft_strjoin(heredoc, "\n");
            free(heredoc);
            input = ft_lstnew(tmp);

            if (!input)
            {
                free(tmp);
                if (top)
                    free_list(top);
                break;
            }
            ft_lstadd_last(&top, input);
        }
        //Loop sai normalmente
        ft_free_double_array(token->red->filename);
        token->red->filename = create_double_array(top, lst_size(top));
        if (!token->red->filename)
        {
            printf("ERROR ALLOC DOUBLE ARRAY\n");
        }
        if (top)
            free_list(top);

        cleanup_all(&prompt_info,NULL);
        exit(0);
    }

    int status;
    waitpid(child,&status, 0);
    if(status % 128 == 2)
    {
        prompt_info.builtins->exit_code = 130;
        write(1,"\n", 1);
    }
    set_signals();
    return;
}
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
/*
    if(token->red->fd == -5)
    {
        prompt_info.builtins->exit_code = 1;
       //Roda comando a mesma
        return;
    }
*/
    if (token->red->fd == -4)
    {
        runcmd(token->previous, env, prompt_info);

        return ;
    }
    else
    {
        if(pipe(pipes) == -1)
            return;
        if (fork() == 0)
        {
            close(pipes[0]);
            while (token->red->filename[i])
            {
                ft_putstr_fd(token->red->filename[i], pipes[1]);
                // ft_putstr_fd("\n", pipes[1]);
                i++;
            }
            cleanup_all(&prompt_info,token);
            exit(0);
        }
        wait(NULL);
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
        wait(NULL);
    }
}
