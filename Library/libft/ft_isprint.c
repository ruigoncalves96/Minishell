/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:37:39 by randrade          #+#    #+#             */
/*   Updated: 2024/04/18 14:50:33 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int     main(void)
{
        int     c = '\0';

	printf("----- ft_isprint -----\n");
        while (c <= 127)
        {
                if (ft_isprint(c) != 0)
                        printf("%c : is print\n", c);
                else
                        printf("%c : is not print\n", c);
                c++;
        }
	printf("\n");
	c = '\0';
	printf("----- isprint -----\n");
	while (c <= 127)
	{
		if (isprint(c) != 0)
			printf("%c : is print\n", c);
		else	
			printf("%c : is not print\n", c);
		c++;
	}
}*/
