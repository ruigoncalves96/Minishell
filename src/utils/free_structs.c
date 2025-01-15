/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:02:40 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 16:53:39 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp);
	}
}

void	ft_free_token_list(t_token *tokens_list)
{
	t_token	*temp;

	while (tokens_list)
	{
		temp = tokens_list;
		tokens_list = tokens_list->next;
		if (tokens_list->red)
		{
			ft_free_double_array(tokens_list->red->filename);
			free(tokens_list->red);
		}
		ft_free_double_array(temp->token);
		free(temp);
	}
}
