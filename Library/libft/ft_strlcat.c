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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= size)
		return (src_len + size);
	else
		size -= dst_len;
	ft_strlcpy(dst + dst_len, src, size);
	return (dst_len + src_len);
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
