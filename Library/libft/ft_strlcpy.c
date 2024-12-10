/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:27:07 by randrade          #+#    #+#             */
/*   Updated: 2024/04/17 15:17:18 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == NULL || src == NULL || !size)
		return (src_len);
	while (*src && --size)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}
/*
#include <string.h>
#include <stddef.h>
#include <stdio.h>

int	main(void)
{
	char	*str = "HELLO WORLD!";
	char	dest[15];
	size_t	size = 13;
	size_t	x;

	printf("String src before function: %s\n", str);
	printf("String dest before function: %s\n", dest);
	
	x = ft_strlcpy(dest, str, size);

	printf("String src: %s\n", str);
	printf("String dest: %s\n", dest);
	if (x)
		printf("String dest last byte character: %d\n", dest[size - 1]);
	printf("%zu\n", x);

	return (0);
}*/
