/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:02:40 by randrade          #+#    #+#             */
/*   Updated: 2025/03/03 14:14:40 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if(temp->str)
		    free(temp->str);
		free(temp);
	}
}

void	free_token_list(t_token *tokens_list)
{
	t_token	*temp;

	while (tokens_list)
	{
		temp = tokens_list;
		tokens_list = tokens_list->next;
		if (temp->token)
	        ft_free_double_array(temp->token);
		if (temp->red)
		{
			ft_free_double_array(temp->red->filename);
			free(temp->red);
		}
		free(temp);
	}
}

void    free_token_tree(t_token *token_tree)
{
    if (token_tree->previous)
        free_token_tree(token_tree->previous);
    if (token_tree->next)
        free_token_tree(token_tree->next);
    if (token_tree->token)
	    ft_free_double_array(token_tree->token);
	if (token_tree->red)
	{
		ft_free_double_array(token_tree->red->filename);
		free(token_tree->red);
	}
	free(token_tree);
}
