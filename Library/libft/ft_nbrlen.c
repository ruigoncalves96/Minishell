/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:49:18 by randrade          #+#    #+#             */
/*   Updated: 2024/10/22 12:49:53 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(int nbr)
{
	size_t	count;

	count = 0;
	if (nbr == 0)
		return (1);
	else if (nbr < 0)
		nbr *= -1;
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}
