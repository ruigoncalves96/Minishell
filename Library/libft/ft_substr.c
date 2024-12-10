/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:58:46 by randrade          #+#    #+#             */
/*   Updated: 2024/12/05 18:10:57 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	char			*ptr;

	s_len = ft_strlen(s);
	if (start >= s_len || !len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Free the duck!";
	char	*str2 = ft_substr("hola", 0, 0);

	printf("%s\n", str);
	printf("%s\n", str2);
	printf("%d\n", ft_strlen(str2));

	free(str2);
}*/
