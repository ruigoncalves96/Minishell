/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:45:09 by randrade          #+#    #+#             */
/*   Updated: 2024/04/26 22:08:26 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>

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

	t_list	*last_list = ft_lstlast(head);
	
	printf("Head List address: %p\n", head);
	printf("\nList 1 address: %p\n", head);
	printf("List 1 content: %s\n", (char *)head->content);
	printf("List 1 next: %p\n", head->next);
	printf("\nList 2 address: %p\n", head->next);
	printf("List 2 content: %s\n", (char *)head->next->content);
	printf("List 2 next: %p\n", head->next->next);
	printf("\nList 3 address: %p\n", head->next->next);
	printf("List 3 content: %s\n", (char *)head->next->next->content);
	printf("List 3 next: %p\n", head->next->next->next);
	
	printf("\nLast List content: %s\n", (char *)last_list->content);

	free(head->next->next);
	free(head->next);
	free(head);
	
	head = NULL;
}
*/
/*

----- Parameters -----

	lst: The beginning of the list.

----- Return Value -----

	Last node of the list.

----- External functs -----

	None.

----- Description -----

	Returns the last node of the list.

*/
