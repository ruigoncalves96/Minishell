/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:53 by randrade          #+#    #+#             */
/*   Updated: 2024/04/26 20:41:44 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *) malloc(sizeof(*lst));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*current;

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
	printf("List 3 next: %p\n", head->next->next->next);

	free(head->next->next);
	free(head->next);
	free(head);

	head = NULL;
}*/
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
