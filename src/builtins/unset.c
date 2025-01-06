#include "../../includes/minishell.h"

/**
 * @brief Shifts environment array one position left starting from given index
 * @param env Array of environment variables
 * @param start_index Index to start shifting from
 */
static void shift_env_left(char **env, int start_index)
{
    int i = start_index;
    
    while (env[i])
    {
        env[i] = env[i + 1];
        i++;
    }
    env[i] = NULL;
}


/**
 * @brief Updates environment size after variable removal
 * @param vars Structure containing environment variables
 * @param size Current size of environment
 * @return 1 on success, 0 on failure
 */
static int update_size_env(t_builtins *vars, int size)
{
    char **new_env;

    new_env = create_new_env(vars->minishell_env, size);
    if (!new_env)
        return (0);
    free(vars->minishell_env);
    vars->minishell_env = new_env;
    return (1);
}

/**
 * @brief Main function to unset an environment variable
 * @param vars Structure containing environment variables
 * @param key_to_remove Key to be removed from environment
 * @return 1 on success, 0 on failure
 */
int unset_variable(t_builtins *vars, char *key_to_remove)
{
    int size = 0;
    int i = 0;
    char *key;
    bool updated = false;

    // Calculate the current size
    while (vars->minishell_env[size])
        size++;

    // Iterate over environment variables
    while (vars->minishell_env[i])
    {
        key = get_key(vars->minishell_env[i]);
        if (!key)
            return (0);

        if (ft_strcmp(key, key_to_remove) == 0)
        {
            free(vars->minishell_env[i]); 
            shift_env_left(vars->minishell_env, i); 
            updated = true; 
            free(key);
            break;
        }

        free(key); 
        i++;
    }

    if (updated)
        return update_size_env(vars, size - 1);

    return (1); 
}

