/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:49:36 by randrade          #+#    #+#             */
/*   Updated: 2025/01/03 17:35:25 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}

/*
----- Parameters -----

	lst: The beginning of the list.

----- Return Value -----

	The length of the list.

----- External functs -----

	None.

----- Description -----

	Counts the number of nodes in a list.

*/
