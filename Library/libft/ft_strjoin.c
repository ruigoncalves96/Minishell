/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:37:34 by randrade          #+#    #+#             */
/*   Updated: 2024/12/05 18:08:47 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, s1_len + 1);
	ft_strlcat(ptr, s2, s1_len + s2_len + 1);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str1 = "Free ";
	char	*str2 = "\0"; //"the ducks";
	char	*str3 = ft_strjoin(str1, str2);

	printf("%s\n", str3);

	free(str3);
}*/
