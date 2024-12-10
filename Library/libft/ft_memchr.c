/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:08:01 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 15:17:22 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str = "Hello World!";
	char	c = 'l';

	char	*ptr = (char *)memchr(str, c, 13);
	printf("%s\n\n", ptr);

	char	*ptr1 = (char *)ft_memchr(str, c, 13);
	printf("%s\n", ptr1);
}*/
