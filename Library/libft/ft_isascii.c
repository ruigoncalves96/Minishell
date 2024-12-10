/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:20:33 by randrade          #+#    #+#             */
/*   Updated: 2024/04/18 14:43:28 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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

	printf("----- ft_isascii -----\n");
        while (c <= 255)
        {
                if (ft_isascii(c) != 0)
                        printf("%c : is ascii\n", c);
                else
                        printf("%c : is not ascii\n", c);
                c++;
        }
	printf("\n");
	c = '\0';
	printf("----- isascii -----\n");
        while (c <= 255)
        {
                if (isascii(c) != 0)
                        printf("%c : is ascii\n", c);
                else
                        printf("%c : is not ascii\n", c);
                c++;
        }
}*/
