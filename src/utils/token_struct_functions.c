/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 14:52:44 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_token_last(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	ft_token_delone(t_token *token)
{
	t_token	*previous;
	t_token	*next;

	previous = token->previous;
	next = token->next;
	if (token == NULL)
		return ;
	if (token->token)
		ft_free_double_array(token->token);
	if (previous)
		previous->next = next;
	if (next)
		next->previous = previous;
	free(token);
	token = NULL;
}

void	ft_token_add_last(t_token **token, t_token *new)
{
	t_token	*last;

	if (token == NULL || new == NULL)
		return ;
	if (*token)
	{
		last = ft_token_last(*token);
		last->next = new;
		new->previous = last;
	}
	else
	{
		*token = new;
		new->previous = NULL;
	}
	new->next = NULL;
}

void	ft_token_add_first(t_token **token, t_token *new)
{
	if (token && new)
	{
		new->previous = NULL;
		if (*token)
		{
			new->next = *token;
			(*token)->previous = new;
		}
		else
			new->next = NULL;
		*token = new;
	}
}

t_token	*ft_token_new(char **content, int type, char subtype)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->token = content;
	token->type = type;
	token->subtype = subtype;
	token->red = NULL;
	token->previous = NULL;
	token->next = NULL;
	return (token);
}
