/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:04:59 by randrade          #+#    #+#             */
/*   Updated: 2024/04/18 14:40:49 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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

	printf("----- ft_isalnum -----\n");
        while (c <= 127)
        {
                if (ft_isalnum(c) != 0)
                        printf("%c : is alpha\n", c);
                else
                        printf("%c : is not  alpha\n", c);
                c++;
        }
	printf("\n");
	c = '\0';
	printf("----- isalnum -----\n");
	while (c <= 127)
        {
		if (isalnum(c) != 0)
                        printf("%c : is alpha\n", c);
                else
                        printf("%c : is not  alpha\n", c);
                c++;
        }
}*/
