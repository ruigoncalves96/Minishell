/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:29:24 by randrade          #+#    #+#             */
/*   Updated: 2024/05/01 14:24:11 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = (int)len - 1;
	if (src < dest)
	{
		while (i >= 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "Free the duck!";
	char	str2[] = "Duck!";

	printf("%s\n", str1);
	char	*ptr1 = (char *)memmove(str2, str1, 15);
	printf("%s\n", str2);
	printf("%s\n\n", ptr1);
}*/
