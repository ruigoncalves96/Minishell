/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:11:49 by randrade          #+#    #+#             */
/*   Updated: 2025/01/03 17:43:42 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*i;
	t_list	*temp;

	if (!lst)
		return ;
	i = *lst;
	while (i)
	{
		temp = i;
		i = i->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	*lst = NULL;
}

/*
----- Parameters -----

	lst: The address of a pointer to a node.
	del: The address of the function used to delete the content of the node.

----- Return Value -----
	
	None.

----- External Functs -----

	free.

----- Description -----

	Deletes and frees the given node and every successor of that node,
using the function ’del’ and free(3).
	Finally, the pointer to the list must be set to NULL.

*/
