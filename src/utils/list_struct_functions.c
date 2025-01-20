/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 12:52:36 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstdelone(t_list *lst)
{
	t_list	*previous;
	t_list	*next;

	previous = lst->previous;
	next = lst->next;
	if (lst == NULL)
		return ;
	if (lst->str)
		free(lst->str);
	if (previous)
		previous->next = next;
	if (next)
		next->previous = previous;
	free(lst);
	lst = NULL;
}

void	ft_lstadd_last(t_list **lst, t_list *new_token)
{
	t_list	*last;

	if (lst == NULL || new_token == NULL)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new_token;
		new_token->previous = last;
	}
	else
	{
		*lst = new_token;
		new_token->previous = NULL;
	}
	new_token->next = NULL;
}

void	ft_lstadd_first(t_list **lst, t_list *new_token)
{
	if (lst && new_token)
	{
		new_token->previous = NULL;
		if (*lst)
		{
			new_token->next = *lst;
			(*lst)->previous = new_token;
		}
		else
			new_token->next = NULL;
		*lst = new_token;
	}
}

t_list	*ft_lstnew(char *content)
{
	t_list	*lst;

	lst = ft_calloc(1, sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->str = content;
	lst->type = 0;
	lst->subtype = 0;
	lst->previous = NULL;
	lst->next = NULL;
	return (lst);
}
