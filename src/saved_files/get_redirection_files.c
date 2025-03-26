#include "../../includes/minishell.h"

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
