/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:37:53 by randrade          #+#    #+#             */
/*   Updated: 2024/10/24 14:45:20 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(char *ptr, int nbr)
{
	if (nbr < 0)
	{
		*ptr = '-';
		nbr *= -1;
		ptr++;
	}
	if (nbr < 10)
	{
		*ptr = nbr + 48;
		ptr++;
	}
	else
	{
		ptr = ft_convert(ptr, nbr / 10);
		ptr = ft_convert(ptr, nbr % 10);
	}
	return (ptr);
}

char	*ft_itoa(int nbr)
{
	char	*ptr;
	int		digit_len;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	digit_len = ft_nbrlen(nbr);
	if (nbr < 0)
		digit_len++;
	ptr = ft_calloc((digit_len + 1), sizeof(char));
	if (ptr != NULL)
	{
		ft_convert(ptr, nbr);
		ptr[digit_len] = '\0';
	}
	return (ptr);
}
/*
----- Parameters -----

	n: the integer to convert.

----- Return value -----

	The string representing the integer.
	NULL if the allocation fails.

----- External functs -----

	malloc.

----- Description -----

	Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
	Negative numbers must be handled.
   */
