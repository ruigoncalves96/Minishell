/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:27:33 by randrade          #+#    #+#             */
/*   Updated: 2024/04/17 15:15:38 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "Hello World!";
	char	str2[] = "000000000";

	memcpy(str2, str1, 5);
	printf("%s\n", str1);
	printf("%s\n\n", str2);
		
	char	*ptr = (char *)ft_memcpy(str2, str1, 5);
	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%s\n", ptr);
}*/

/*
   The memcpy() function copies n bytes from memory area src to memory area dst.
   If dst and src overlap, behavior is undefined.
   Applications in which dst and src might overlap should use memmove instead.
*/
