/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:59:58 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 15:13:17 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c && *s)
		s++;
	if (*s != (unsigned char)c)
		return (NULL);
	return ((char *)s);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*s = "Hello World!";
	int	c = 'l';

	printf("string : %s\n\n", s);
	printf("char : %c\n\n", c);
	printf("string : %s\n", ft_strchr(s, c));
}*/
