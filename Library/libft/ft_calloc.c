/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:59 by randrade          #+#    #+#             */
/*   Updated: 2024/04/17 15:12:46 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str1 = (char *) calloc(0, 0);
	char	*str2 = (char *) ft_calloc(0, 0);
	int	i;

	printf("Calloc:");
	i = 0;
	while (i < sizeof(str1))
	{
		printf("%d", str1[i]);
		i++;
	}
	printf("\n");
	printf("ft_calloc:");
	i = 0;
	while (i < sizeof(str2))
	{
		printf("%d", str2[i]);
		i++;
	}
	printf("\n");
	free(str1);
	free(str2);
}*/
