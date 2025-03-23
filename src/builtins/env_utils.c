#include "../../includes/minishell.h"

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
		shlvl_number = 1;
    else
    {
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

