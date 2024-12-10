/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:31:52 by randrade          #+#    #+#             */
/*   Updated: 2024/04/26 22:23:39 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del)
		del(lst->content);
	free(lst);
	lst = NULL;
}
/*
#include <stdio.h>

void	ft_del_content(void *content)
{
	free(content);
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
	printf("List 3 next: %p\n", head->next->next->next);

	ft_lstdelone(ft_lstlast(head), NULL);

	printf("\nHead List address: %p\n", head);
	printf("\nList 1 address: %p\n", head);
	printf("List 1 content: %s\n", (char *)head->content);
	printf("List 1 next: %p\n", head->next);
	printf("\nList 2 address: %p\n", head->next);
	printf("List 2 content: %s\n", (char *)head->next->content);
	printf("List 2 next: %p\n", head->next->next);
	printf("\nList 3 address: %p\n", head->next->next);
	printf("List 3 content: %s\n", (char *)head->next->next->content);
	printf("List 3 next: %p\n", head->next->next->next);
	
	free(head->next);
	free(head);
}
*/
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
