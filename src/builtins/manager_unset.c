#include "../../includes/minishell.h"

static void remove_env_node(t_env *env, t_env_var *current)
{
    if (current->prev)
        current->prev->next = current->next;
    if (current->next)
        current->next->prev = current->prev;
    
    if (current == env->vars)
        env->vars = current->next;

    free(current->key);
    free(current->value);
    free(current);
    
    env->var_count--;
}
/**
 * @brief Unset a variable to the environment
 * @param env Environment structure
 * @param key key_to_unset
 * @return 1 on sucess,0 on not found, -1 on error
 */
int unset_env_var(t_env *env, char *key_to_unset)
{
    if (!env || !key_to_unset || !env->vars)
        return -1;

    t_env_var *current;
    t_env_var *next;

    current = env->vars;
    while (current)
    {
        next = current->next;
        if (ft_strcmp(current->key, key_to_unset) == 0)
        {
            remove_env_node(env, current);
            return 1; 
        }
        current = next; 
    }
    
    return 0; 
}

int manager_unset(char **str, t_env *env)
{
    if (str == NULL || *str == NULL || array_size(str) == 1)
    {
        return 1;
    }

        int i;
        if(array_size(str) >= 2)
        {
            i = 1;
            while(str[i])
            {
                unset_env_var(env,str[i]);
                i++;
            }
        }
        return 0;
}
