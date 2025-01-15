#include "../../includes/minishell.h"

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
