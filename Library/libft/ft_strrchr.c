/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:32:13 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 16:42:09 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if ((unsigned char)c == s[i])
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
          const char      *s = "Free the duck!";
          int     c = 'e';
 
          printf("string : %s\n\n", s);
          printf("char : %c\n\n", c);
          printf("string : %s\n", ft_strrchr(s, c));
          printf("string : %s\n", strrchr(s, c));
}*/
