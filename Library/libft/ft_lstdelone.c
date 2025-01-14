/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:31:52 by randrade          #+#    #+#             */
/*   Updated: 2025/01/14 17:15:11 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*
----- Parameters -----

	lst: The node to free.
	del: The address of the function used to delete the content.

----- Return Value -----

	None.

----- External Functs -----

	Free.

----- Description -----

	Takes as a parameter a node and frees the memory of the node’s
content using the function ’del’ given as a parameter and free the node.
	The memory of ’next’ must not be freed.

*/
