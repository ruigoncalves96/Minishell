/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:01:21 by randrade          #+#    #+#             */
/*   Updated: 2024/12/05 18:07:46 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		size;

	size = ft_strlen(s1);
	ptr = ft_calloc(size + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, size + 1);
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "Hello World!";
	char	*str2 = strdup(str);
	char	*str3 = ft_strdup(str);
	
	str[0] = 'R';
	printf("%s\n", str);
	printf("%s\n", str2);
	printf("%d\n", str2[12]);
	printf("%s\n", str3);
	printf("%d\n", str3[12]);
}*/
