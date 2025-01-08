/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/07 15:53:33 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **content)
{
	t_list	*lst;

	lst = (t_list *) ft_calloc(1, sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->str = content;
	lst->type = 0;
	lst->subtype = 0;
	lst->previous = NULL;
	lst->next = NULL;
	return (lst);
}

/*
----- Parameters -----

	content: The content to create the node with.

----- Return Value -----

	The new node.

----- External functs -----

	malloc.

----- Description -----

	Allocates (with malloc(3)) and returns a new node.
	The member variable ’content’ is initialized with
the value of the parameter ’content’.
	The variable ’next’ is initialized to NULL.

*/
