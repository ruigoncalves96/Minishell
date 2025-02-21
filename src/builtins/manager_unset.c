#include "../../includes/minishell.h"

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

    t_env_var *current = env->vars;
    t_env_var *next;

    while (current)
    {
        // Store next pointer before potentially freeing current
        next = current->next;
        
        if (ft_strcmp(current->key, key_to_unset) == 0)
        {
            if (current->prev)
                current->prev->next = current->next;
            if (current->next)
                current->next->prev = current->prev;
            
            if (current == env->vars)
                env->vars = current->next;

            // Free the node
            free(current->key);
            free(current->value);
            free(current);
            
            env->var_count--;
            return 1; 
        }
        current = next; 
    }
    
    return 0; 
}


int manager_unset(char **str, t_env *env)
{
       if (str == NULL || *str == NULL)
       {
        return 1;
       }

        int i;
        
        if(array_size(str) == 1)
            return 1;
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
