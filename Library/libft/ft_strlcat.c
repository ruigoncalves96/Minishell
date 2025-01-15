/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:11:11 by randrade          #+#    #+#             */
/*   Updated: 2024/04/17 23:45:51 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size <= destlen)
		return (srclen + size);
	i = 0;
	while (src[i] != '\0' && destlen + i < size - 1)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
/*
#include <string.h>
#include <stddef.h>
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello World!";
	char	dest[15] = "xxx";
	size_t	size = 10;
	size_t	x;

	printf("Src: %s\n", str);
	printf("Dest before function: %s\n\n", dest);

	x = strlcat(dest, str, size);

	printf("Dest after function: %s\n\n", dest);	
	if (x)
		printf("String dest last byte character: %d\n", dest[ft_strlen(dest)]);
	printf("%zu\n", x);
}*/
