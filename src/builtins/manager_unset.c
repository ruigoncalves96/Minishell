/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:39:04 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/24 12:39:28 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_node(t_env *env, t_env_var *current)
{
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	if (current == env->vars)
		env->vars = current->next;
	free(current->key);
	free(current->value);
	free(current);
	env->var_count--;
}
/**
 * @brief Unset a variable to the environment
 * @param env Environment structure
 * @param key key_to_unset
 * @return 1 on sucess,0 on not found, -1 on error
 */

int	unset_env_var(t_env *env, char *key_to_unset)
{
	t_env_var	*current;
	t_env_var	*next;

	if (!env || !key_to_unset || !env->vars)
		return (-1);
	current = env->vars;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->key, key_to_unset) == 0)
		{
			remove_env_node(env, current);
			return (1);
		}
		current = next;
	}
	return (0);
}

int	manager_unset(char **str, t_env *env)
{
	int	i;

	if (str == NULL || *str == NULL || array_size(str) == 1)
	{
		return (1);
	}
	if (array_size(str) >= 2)
	{
		i = 1;
		while (str[i])
		{
			unset_env_var(env, str[i]);
			i++;
		}
	}
	return (0);
}
