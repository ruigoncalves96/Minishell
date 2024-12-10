/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:51:30 by randrade          #+#    #+#             */
/*   Updated: 2024/04/26 22:51:32 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>

void	ft_strprint(void *s)
{
	printf("%s\n", (char *)s);
}

int	main(void)
{
	t_list  *head;
	t_list  *new_node;
	t_list  *current;
	
	new_node = ft_lstnew("Free");
	head = new_node;
	current = new_node;
	new_node = ft_lstnew("the");
	current->next = new_node;
	current = new_node;
	new_node = ft_lstnew("Duck!");
	current->next = new_node;
	
	printf("Head List address: %p\n", head);
	printf("\nList 1 address: %p\n", head);
	printf("List 1 content: %s\n", (char *)head->content);
	printf("List 1 next: %p\n", head->next);
	printf("\nList 2 address: %p\n", head->next);
	printf("List 2 content: %s\n", (char *)head->next->content);
	printf("List 2 next: %p\n", head->next->next);
	printf("\nList 3 address: %p\n", head->next->next);
	printf("List 3 content: %s\n", (char *)head->next->next->content);
	printf("List 3 next: %p\n\n", head->next->next->next);
	
	ft_lstiter(head, &ft_strprint);

	free(head->next->next);
	free(head->next);
	free(head);
}
*/
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
