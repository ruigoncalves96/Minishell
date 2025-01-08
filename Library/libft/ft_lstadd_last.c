/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:08:58 by randrade          #+#    #+#             */
/*   Updated: 2025/01/06 13:09:22 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_last(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->previous = last;
	}
	else
	{
		*lst = new;
		new->previous = NULL;
	}
	new->next = NULL;
}

/*

----- Parameters -----

	lst: The address of a pointer to the first link of a list.
	new: The address of a pointer to the node to be added to the list.

----- Return Value -----

	None.

----- External functs. -----

	None.

----- Description -----

	Adds the node ’new’ at the end of the list.

*/
