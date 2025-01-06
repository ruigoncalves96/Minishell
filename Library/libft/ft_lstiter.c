/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:51:30 by randrade          #+#    #+#             */
/*   Updated: 2025/01/05 16:03:04 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, char **(*f)(char **))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->str);
		lst = lst->next;
	}
}

/*
----- Parameters -----

	lst: The address of a pointer to a node.
	f: The address of the function used to iterate on the list.

----- Return Value -----

	None.

----- External Functs -----

	None.

----- Description -----

	Iterates the list ’lst’ and applies the function ’f’ on the content
of each node.

*/
