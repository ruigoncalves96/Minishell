#include "../../includes/minishell.h"

static int is_valid_env_name(const char *key)
{
    int i;

    if (!key || !key[0])
        return 0;
    
    // First character must be alphabetic or underscore
    if (!ft_isalpha(key[0]) && key[0] != '_')
        return 0;
        
    // Rest can be alphanumeric or underscore
    i = 1;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

static int validate_and_handle_key(char *key, char *value,t_builtins *builtins)
{
    if (key == NULL || ft_strlen(key) == 0)
    {
        print_error("export",value,NOT_VALID_IDENTIFIER,true);
        free(key);
        free(value);
        builtins->exit_code = 1;
        return 0;
    }
    
    if (!is_valid_env_name(key))
    {
        print_error("export",key,NOT_VALID_IDENTIFIER,true);
        free(key);
        free(value);
        builtins->exit_code = 1;
        return 0;
    }
    return 1;
}

static void handle_key_value(t_env *env, char *key, char *value)
{
    if (value == NULL)
        set_export_only(env, key, 1);
    else
        export_env_var(env, key, value, 0);
    free(key);
    free(value);
}

static int process_multiple_exports(char **str, t_env *env,t_builtins *builtins)
{
    int i = 1;
    while (str[i] != NULL)
    {
        char *key = get_key(str[i]);
        char *value = get_value(str[i]);
        
        if (!validate_and_handle_key(key, value,builtins))
        {
            i++;
            continue;
        }
        handle_key_value(env, key, value);
        i++;
    }
    return 0;
}

int export_manager(char **str, t_env *env,t_builtins *builtins)
{
    if (str == NULL || *str == NULL)
        return 1;

    if (array_size(str) == 1)
    {
        handle_export(env);
        return 0;
    }
        
    if (array_size(str) >= 2)
        return process_multiple_exports(str, env,builtins);
        
    return 0;
}
