/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:39:45 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/28 18:05:01 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_var	*create_env_node(char *env_str)
{
	t_env_var	*var;

	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->key = get_key(env_str);
	var->value = get_value(env_str);
	var->is_export_only = 0;
	if (!var->key || !var->value)
	{
		free(var->key);
		free(var->value);
		free(var);
		return (NULL);
	}
	var->prev = NULL;
	var->next = NULL;
	return (var);
}

void	append_env_var(t_env_var **head, t_env_var *new_var)
{
	t_env_var	*current;

	if (!*head)
	{
		*head = new_var;
		new_var->prev = NULL;
		return ;
	}
	current = *head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_var;
	new_var->prev = current;
	new_var->next = NULL;
}

static void	apeend_env_to_list(char **envp, t_env *env)
{
	int			i;
	t_env_var	*new_var;

	i = 0;
	while (envp[i])
	{
		new_var = create_env_node(envp[i]);
		if (!new_var)
		{
			free_env(env);
			return ;
		}
		append_env_var(&env->vars, new_var);
		env->var_count++;
		i++;
	}
}

static void	create_vars_env_flag(t_env *env)
{
	char	*pwd;

	export_env_var(env, "SHLVL", "1", 0);
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		export_env_var(env, "PWD", pwd, 0);
		free(pwd);
	}
	export_env_var(env, "PATH",
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 0);
	export_env_var(env, "_", "/usr/bin/env", 0);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	bool	empty_env;

	empty_env = false;
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->vars = NULL;
	env->var_count = 0;
	if (!envp || !envp[0])
	{
		empty_env = true;
		create_vars_env_flag(env);
	}
	else
	{
		apeend_env_to_list(envp, env);
	}
	if (!empty_env)
		update_shlvl(env);
	return (env);
}
