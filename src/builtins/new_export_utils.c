/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:40:22 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/24 12:40:24 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env_var	*create_node_copy_env(t_env_var *current)
{
	t_env_var	*new_node;

	new_node = ft_calloc(1, sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(current->key);
	new_node->is_export_only = current->is_export_only;
	if (current->value)
		new_node->value = ft_strdup(current->value);
	else
		new_node->value = NULL;
	return (new_node);
}

static void	append_to_list(t_env_var **copy, t_env_var *new_node)
{
	t_env_var	*temp;

	if (!*copy)
	{
		*copy = new_node;
		return ;
	}
	temp = *copy;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

t_env_var	*copy_env_list(t_env_var *list)
{
	t_env_var	*copy;
	t_env_var	*current;
	t_env_var	*new_node;

	copy = NULL;
	current = list;
	while (current)
	{
		new_node = create_node_copy_env(current);
		if (!new_node)
			return (NULL);
		append_to_list(&copy, new_node);
		current = current->next;
	}
	return (copy);
}
