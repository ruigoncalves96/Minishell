/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 01:03:49 by randrade          #+#    #+#             */
/*   Updated: 2024/04/26 23:12:47 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new_node;

	if (!lst)
		return (NULL);
	map = NULL;
	while (lst)
	{
		if (f)
			new_node = ft_lstnew(f(lst->content));
		else
			new_node = ft_lstnew(lst->content);
		if (new_node == NULL)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, new_node);
		lst = lst->next;
	}
	return (map);
}
/*
#include <stdio.h>

void	*ft_strprint(void *s)
{
	printf("%s\n", (char *)s);
	return (s);
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
	
	t_list	*new_head = ft_lstmap(head, &ft_strprint, NULL);

	printf("\nHead List address: %p\n", new_head);
	printf("\nList 1 address: %p\n", new_head);
	printf("List 1 content: %s\n", (char *)new_head->content);
	printf("List 1 next: %p\n", new_head->next);
	printf("\nList 2 address: %p\n", new_head->next);
	printf("List 2 content: %s\n", (char *)new_head->next->content);
	printf("List 2 next: %p\n", new_head->next->next);
	printf("\nList 3 address: %p\n", new_head->next->next);
	printf("List 3 content: %s\n", (char *)new_head->next->next->content);
	printf("List 3 next: %p\n", new_head->next->next->next);
	
	free(head->next->next);
	free(head->next);
	free(head);
	free(new_head->next->next);
	free(new_head->next);
	free(new_head);
}
*/
/*

----- Parameters -----

	lst: The address of a pointer to a node.
	f: The address of the function used to iterate on the list.
	del: The address of the function used to delete the content of
a node if needed.

----- Return Value -----

	The new list.
	NULL if the allocation fails.

----- External functs -----

	malloc, free.

----- Description -----

	Iterates the list ’lst’ and applies the function ’f’ on the content 
of each node. 
	Creates a new list resulting of the successive applications of
the function ’f’. 
	The ’del’ function is used to delete the content of a node if needed.

*/
