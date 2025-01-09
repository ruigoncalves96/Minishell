#include "../../includes/minishell.h"

/**
 * @brief Exports or updates an environment variable
 * @param vars Builtins Structure 
 * @param key_to_find Key to search in the environment
 * @param new_value New complete value in "key=value" format
 * @return 1 on success, 0 on error
 */
char **create_new_env(char **old_env, int size)
{
    char **new_env;
    int i;

    new_env = malloc(sizeof(char *) * (size + 2));
    if (!new_env)
        return (NULL);
    i = 0;
    while (i < size)
    {
        new_env[i] = old_env[i];
        i++;
    }
    new_env[size + 1] = NULL;
    return (new_env);
}

int add_new_variable(t_builtins *vars, char *new_value, int size)
{
    char **new_env;

    new_env = create_new_env(vars->minishell_env, size);
    if (!new_env)
        return (0);
    new_env[size] = ft_strdup(new_value);
    if (!new_env[size])
    {
        free(new_env);
        return (0);
    }
    free(vars->minishell_env);
    vars->minishell_env = new_env;
    return (1);
}

int update_existing_var(t_builtins *vars, char *key_to_find, 
    char *new_value, char *key)
{
    int i;

    i = 0;
    while (vars->minishell_env[i])
    {
        if (ft_strcmp(key, key_to_find) == 0)
        {
            free(vars->minishell_env[i]);
            vars->minishell_env[i] = ft_strdup(new_value);
            if (!vars->minishell_env[i])
                return (0);
            return (1);
        }
        i++;
    }
    return (0);
}

int export_variable(t_builtins *vars, char *key_to_find, char *new_value)
{
    int i;
    int size;
    char *key;
    bool found;
    int update_status;

    if (!vars || !vars->minishell_env || !key_to_find || !new_value)
        return (0);
    size = 0;
    while (vars->minishell_env[size])
        size++;
    i = 0;
    found = false;
    while (vars->minishell_env[i] && !found)
    {
        key = get_key(vars->minishell_env[i]);
        if (!key)
            return (0);
        update_status = update_existing_var(vars, key_to_find, new_value, key);
        if (update_status == 1)
            found = true;
        free(key);
        i++;
    }
    if (!found)
        return (add_new_variable(vars, new_value, size));
    return (1);
}

// Extrai nome da variável de uma string no formato VAR=VALUE
char *get_key(char *env)
{
    int len = 0;
    while (env[len] && env[len] != '=')
        len++;
    char *key = ft_calloc(len + 1,1);
    if (!key)
        return NULL;
    ft_strlcpy(key, env, len + 1);
    return key;
}