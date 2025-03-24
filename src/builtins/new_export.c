/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:42:50 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/24 12:42:52 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_x_declaration_list(t_env_var *vars)
{
	t_env_var	*current;

	current = vars;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

static void	swap_node_values(t_env_var *a, t_env_var *b)
{
	char	*temp_key;
	char	*temp_value;
	int		temp_flag;

	temp_key = a->key;
	temp_value = a->value;
	temp_flag = a->is_export_only;
	a->key = b->key;
	a->value = b->value;
	a->is_export_only = b->is_export_only;
	b->key = temp_key;
	b->value = temp_value;
	b->is_export_only = temp_flag;
}

static void	sort_env_list(t_env_var *head)
{
	t_env_var	*current;
	int			sorted;

	if (!head)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = head;
		while (current->next)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap_node_values(current, current->next);
				sorted = 0;
			}
			current = current->next;
		}
	}
}

static void	free_env_copy(t_env_var *list)
{
	t_env_var	*current;

	while (list)
	{
		current = list;
		list = list->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}

void	handle_export(t_env *env)
{
	t_env_var	*env_copy;

	env_copy = copy_env_list(env->vars);
	if (!env_copy)
		return ;
	sort_env_list(env_copy);
	print_x_declaration_list(env_copy);
	free_env_copy(env_copy);
}
