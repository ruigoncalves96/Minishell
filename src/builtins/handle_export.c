#include "../../includes/minishell.h"

static int process_single_export(t_env *env)
{
    handle_export(env);
    return 0;
}

static int validate_and_handle_key(char *key, char *value)
{
    if (key == NULL || ft_strlen(key) == 0)
    {
        printf("Maroto andas a usar caracteres que nao deves\n");
        free(key);
        free(value);
        return 0;
    }
    return 1;
}

static void handle_key_value(t_env *env, char *key, char *value)
{
    if (value == NULL)
        set_export_only(env, key, 1);
    else
    {
      //  printf("key = %s\n", key);
       // printf("value = %s\n", value);
        export_env_var(env, key, value, 0);
    }
    free(key);
    free(value);
}

static int process_multiple_exports(char **str, t_env *env)
{
    int i = 1;
    while (str[i] != NULL)
    {
        char *key = get_key(str[i]);
        char *value = get_value(str[i]);
        
        if (!validate_and_handle_key(key, value))
        {
            i++;
            continue;
        }
        handle_key_value(env, key, value);
        i++;
    }
    return 0;
}

int export_manager(char **str, t_env *env)
{
    if (str == NULL || *str == NULL)
        return 1;

  //  printf("ArraySize = %d\n", array_size(str));
    
    if (array_size(str) == 1)
        return process_single_export(env);
        
    if (array_size(str) >= 2)
        return process_multiple_exports(str, env);
        
    return 0;
}