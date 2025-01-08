#include "../../includes/minishell.h"

void append_env_var(t_env_var **head, t_env_var *new_var)
{
    if (!*head)
    {
        *head = new_var;
        return;
    }

    t_env_var *current = *head;
    while (current->next)
    {
        current = current->next;
    }
    current->next = new_var;
}

/**
 * @brief Initialize environment linked list
 * @param envp Original environment array
 * @return Pointer to new env structure or NULL if error
 */
t_env *init_env(char **envp)
{
    t_env *env;
    int i;

    env = ft_calloc(1,sizeof(t_env));
    if (!env)
        return NULL;

    env->vars = NULL;
    env->var_count = 0; // vai ser bom no futuro para funções como o shell LVL
    env->env_array = NULL;

    i = 0;
    while (envp[i])
    {
        t_env_var *new_var = create_env_node(envp[i]);
        if (!new_var)
        {
            free_env(env);
            return NULL;
        }
        append_env_var(&env->vars, new_var);
        env->var_count++;
        i++;
    }
    return env;
}

/**
 * @brief Get value part from environment string
 * @param env_str String in format "KEY=VALUE"
 * @return Value string or NULL if error
 */
char *get_value(char *env_str)
{
    char *equals = ft_strchr(env_str, '=');
    if (!equals)
        return NULL;
    return ft_strdup(equals + 1);
}

/**
 * @brief Create new environment variable node
 * @param env_str String in format "KEY=VALUE"
 * @return New node or NULL if error
 */
t_env_var *create_env_node(char *env_str)
{
    t_env_var *var = ft_calloc(1,sizeof(t_env_var));
    if (!var)
        return NULL;

    var->key = get_key(env_str);
    var->value = get_value(env_str);
    
    if (!var->key || !var->value)
    {
        free(var->key);
        free(var->value);
        free(var);
        return NULL;
    }
    
    var->next = NULL;
    return var;
}
/**
 * @brief Free entire environment structure
 * @param env Environment structure to free
 */
void free_env(t_env *env)
{
    if (!env)
        return;

    t_env_var *current = env->vars;
    while (current)
    {
        t_env_var *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }

    free(env);
}

void print_env_list(t_env *env)
{
    t_env_var *current;

    if (!env || !env->vars)
        return;

    current = env->vars;
    while (current)
    {

        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}