#include "../../includes/minishell.h"

/**
 * @brief Exports or updates an environment variable
 * @param vars Builtins Structure 
 * @param key_to_find Key to search in the environment
 * @param new_value New complete value in "key=value" format
 * @return 1 on success, 0 on error
 */
int export_variable(t_builtins *vars, char *key_to_find, char *new_value)
{
    if (!vars || !vars->minishell_env || !key_to_find || !new_value)
        return 0;

    int i = 0;
    char *key;
    bool found = false;

    while (vars->minishell_env[i])
    {
        key = get_key(vars->minishell_env[i]);
        if (!key)
            return 0;
        if (ft_strcmp(key, key_to_find) == 0) {
            free(vars->minishell_env[i]);
            vars->minishell_env[i] = ft_strdup(new_value);
            if (!vars->minishell_env[i])
            {
                free(key);
                return 0;
            }
            found = true;
        }
        free(key);
        if (found)
            break;
        i++;
    }

    if (!found)
    {
        vars->minishell_env[i] = ft_strdup(new_value);
        if (!vars->minishell_env[i])
            return 0;
    }
    return 1;
}
