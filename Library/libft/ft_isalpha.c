/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:01:45 by randrade          #+#    #+#             */
/*   Updated: 2024/04/18 14:39:49 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	c = '\0';

	printf("----- ft_isalpha -----\n");
	while (c <= 127)
	{
		if (ft_isalpha(c) != 0)
			printf("%c : is alpha\n", c);
		else	
			printf("%c : is not  alpha\n", c);
		c++;
	}
	printf("\n");
	c = '\0';
	printf("----- isalpha -----\n");
	while (c <= 127)
	{
		if (isalpha(c) != 0)
			printf("%c : is alpha\n", c);
		else	
			printf("%c : is not  alpha\n", c);
		c++;
	}
}*/
