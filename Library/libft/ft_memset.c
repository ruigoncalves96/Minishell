/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:12:40 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 13:43:33 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "Hello World"; 
	char	str2[] = "Hello World";

	memset(str1, '0', 5);
	printf("memset : %s\n", str1);
	ft_memset(str2, '0', 5);
	printf("ft_memset : %s\n", str2);
}*/
