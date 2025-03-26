#include "../../includes/minishell.h"

static bool update_red_arguments(t_token *red_arg_token)
{
    char    **new_red_arg;

    new_red_arg = ft_calloc(2, sizeof(char *));
    if (!new_red_arg)
        return (false);
    new_red_arg[0] = ft_strdup(red_arg_token->token[0]);
    if (!new_red_arg)
        return (ft_free_double_array(new_red_arg), false);
    ft_free_double_array(red_arg_token->token);
    red_arg_token->token = new_red_arg;
    return (true);
}

static bool move_command(char **dest, char **cat_dest, char **src)
{
    size_t  i;

    i = 0;
    while (cat_dest && cat_dest[i])
    {
        dest[i] = ft_strdup(cat_dest[i]);
        if (!dest[i])
            return (ft_free_double_array(dest), false);
        i++;
    }
    while (*src)
    {
        dest[i] = ft_strdup(*src);
        if (!dest[i])
            return (ft_free_double_array(dest), false);
        i++;
        src++;
    }
    dest[i] = NULL;
    return (true);
}

bool    get_redirection_files(t_token *token)
{
    t_token *command;
    char    **red_command;
    char    **new_array;

    command = get_heredoc_command_list(token);
    if (!command)
        return (true);
    red_command = token->next->token + 1;
    new_array = ft_calloc(array_len(command->token) + array_len(red_command) + 1, sizeof(char *));
    if (!new_array)
        return (false);
    if (move_command(new_array, command->token, red_command) == false)
        return (false);
    if (command->token)
        ft_free_double_array(command->token);
    command->token = new_array;
    if (update_red_arguments(token->next) == false)
        return (false);
    return (true);
}
