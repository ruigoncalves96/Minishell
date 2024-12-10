/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:24:34 by randrade          #+#    #+#             */
/*   Updated: 2024/04/18 14:46:09 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
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

	printf("----- ft_isdigit -----\n");
        while (c <= 127)
        {
                if (ft_isdigit(c) != 0)
                        printf("%c : is digit\n", c);
                else    
                        printf("%c : is not digit\n", c);
                c++;
        }
	printf("\n");
	c = '\0';
	printf("----- isdigit -----\n");
        while (c <= 127)
        {
                if (isdigit(c) != 0)
                        printf("%c : is digit\n", c);
                else    
                        printf("%c : is not digit\n", c);
                c++;
        }
}*/
