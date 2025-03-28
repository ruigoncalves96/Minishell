/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:22:31 by randrade          #+#    #+#             */
/*   Updated: 2025/03/28 15:06:11 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_empty_node(t_list *node)
{
	if (node->subtype == T_QUOTE || (node->subtype != T_QUOTE
			&& (!node->previous && !node->next)))
		return (true);
	return (false);
}

char	**get_command_array(t_list **node)
{
	char	**new_token;
	size_t	array_len;
	size_t	i;

	array_len = command_array_len(*node);
	new_token = ft_calloc(array_len + 1, sizeof(char *));
	if (!new_token)
		return (NULL);
	i = 0;
	while (*node && (*node)->type == COMMAND)
	{
		if ((*node)->str[0] != '\0' || check_empty_node(*node) == true)
		{
			new_token[i] = ft_strdup((*node)->str);
			if (new_token[i] == NULL)
				return (ft_free_double_array(new_token), NULL);
			i++;
		}
		*node = (*node)->next;
	}
	new_token[i] = NULL;
	return (new_token);
}
