#include "../../includes/minishell.h"

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

static void create_vars_env_flag(t_env *env)
{
        export_env_var(env, "SHLVL", "1", 0);
         char  *pwd = getcwd(NULL, 0);
           if (pwd)
           {
               export_env_var(env, "PWD", pwd, 0);
               free(pwd);
           }

        export_env_var(env, "PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
        export_env_var(env,"_","/usr/bin/env",0);
}

static void apeend_env_to_list(char **envp,t_env *env)
{
    int i;
     t_env_var *new_var;
    i = 0;
    while (envp[i])
        {
            new_var= create_env_node(envp[i]);
            if (!new_var)
            {
                free_env(env);
                return;
            }
            append_env_var(&env->vars, new_var);
            env->var_count++;
            i++;
        }
}

t_env *init_env(char **envp)
{
    t_env *env;

    env = ft_calloc(1,sizeof(t_env));
    if (!env)
        return NULL;

    env->vars = NULL;
    env->var_count = 0;
    if(!envp || !envp[0])
    {
        create_vars_env_flag(env);
    }else
    {
        apeend_env_to_list(envp,env);
    }
    return env;
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
        if (!current->is_export_only)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void update_shlvl(t_env *env)
{
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
