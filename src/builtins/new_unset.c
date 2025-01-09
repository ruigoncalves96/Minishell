#include "../../includes/minishell.h"

/**
 * @brief Unset a variable to the environment
 * @param env Environment structure
 * @param key key_to_unset
 * @return 1 on sucess,0 on not found, -1 on error
 */
int unset_env_var(t_env *env,char *key_to_unset)
{
    if(!env || !key_to_unset || !env->vars)
        return -1;

    t_env_var *current;

    current = env->vars;
    while (current)
    {
        if(ft_strcmp(current->key,key_to_unset) == 0)
        {
            //Handle pointers
            if(current->prev)
                current->prev->next = current->next;
            if(current->next)
                current->next->prev = current->prev;
            
            if(current == env->vars)
                env->vars = current->next;

            free(current->key);
            free(current->value);
            free(current);
        }
        current = current->next;
    }
    
    return 0;
}
