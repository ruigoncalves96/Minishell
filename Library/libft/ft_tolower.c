/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:52:47 by randrade          #+#    #+#             */
/*   Updated: 2024/04/17 15:18:29 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int	c = 0;

	while (c <= 127)
	{
		printf("%c: %c\n", c, ft_tolower(c));
		c++;
	}
	return (0);
}*/
