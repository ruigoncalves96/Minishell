#include "../../includes/minishell.h"

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

void append_env_var(t_env_var **head, t_env_var *new_var)
{ 
    if (!*head)
    {
        *head = new_var;
        new_var->prev = NULL;
        return;
    }

    t_env_var *current = *head;
    while (current->next)
    {
        current = current->next;
    }
    current->next = new_var;
    new_var->prev =  current;
    new_var->next = NULL;
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
    var->is_export_only = 0;
    
    if (!var->key || !var->value)
    {
        free(var->key);
        free(var->value);
        free(var);
        return NULL;
    }
    
    var->prev = NULL;
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
        if (!current->is_export_only)  // Só mostra se não for export-only
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void update_shlvl(t_env *env)
{

	// [X] Vou perceber qual e o meu shlvl
	char *shlvl_value;
	int shlvl_number;
	char *new_shlvl;

	shlvl_value = get_env_value(env,"SHLVL");
	if(!shlvl_value)
	{
		shlvl_number = 1;
	}else{
		shlvl_number = ft_atoi(shlvl_value);
		shlvl_number++;
	}

	new_shlvl = ft_itoa(shlvl_number);
	if(!new_shlvl)
	{
		ft_putstr_fd("Error Inicializing SHLVL\n",2);
		return ;
	}
	export_env_var(env,"SHLVL",new_shlvl,0);
	free(new_shlvl);
}
/*

void flag_env()
{
    char *pwd;
    char **flag_env;


    flag_env = malloc(sizeof(char *) * 4);
    if (!flag_env)
        return;
    pwd = getcwd(NULL, 0); 
    if(pwd == NULL)
    {
        printf("Deu erro dentro da funcao flag_env guardar o pwd");
        return;
    }
    flag_env[0] = ft_strdup(pwd);
    free(pwd);
    flag_env[1] = ft_strdup("SHLVL=1");
    flag_env[2] = ft_strdup("_=/usr/bin/env");
    flag_env[3] = NULL;
    ft_print_double_array(flag_env);
    free_double_array(flag_env);
}
*/