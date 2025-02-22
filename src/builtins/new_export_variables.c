#include "../../includes/minishell.h"

static t_env_var *find_env_var(t_env *env, const char *key)
{
    t_env_var *current = env->vars;
    
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
void set_export_only(t_env *env, const char *key, int is_export_only)
{
    t_env_var *current;
    t_env_var *new_var;

    current = env->vars;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            current->is_export_only = is_export_only;
            return;
        }
        current = current->next;
    }
    new_var = ft_calloc(1, sizeof(t_env_var));
    if (!new_var)
        return;

    new_var->key = ft_strdup(key);
    new_var->value = NULL;
    new_var->is_export_only = is_export_only;
    new_var->next = env->vars;
    if (env->vars)
        env->vars->prev = new_var;
    env->vars = new_var;
    env->var_count++;
}
static int export_new_var_to_env(t_env *env, const char *key, const char *value,int is_export_only)
{
        t_env_var *new_var;

        new_var = ft_calloc(1,sizeof(t_env_var));
        if (!new_var)
            return -1;
        
        new_var->key = ft_strdup(key);
        new_var->value = ft_strdup(value);
        new_var->is_export_only = is_export_only;
        new_var->next = NULL;
        
        if (!new_var->key || !new_var->value)
        {
            free(new_var->key);
            free(new_var->value);
            free(new_var);
            return -1;
        }
        // Append to end of list
        append_env_var(&env->vars, new_var);
        env->var_count++;
        return 0;
}
int export_env_var(t_env *env, const char *key, const char *value,int is_export_only)
{
    if (!env || !key || !value)
        return -1;

    t_env_var *existing;
    char *new_value;

    existing= find_env_var(env, key);
    if (existing)
    {
        // Update existing variable's value
        new_value = ft_strdup(value);
        if (!new_value)
            return -1;
            
        free(existing->value);
        existing->value = new_value;
        existing->is_export_only = is_export_only;
    }
    else
        export_new_var_to_env(env,key,value,is_export_only);
        
    return 0;
}

