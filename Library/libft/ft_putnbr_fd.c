/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:55:53 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 13:11:11 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			n *= -1;
			write(fd, "-", 1);
			ft_putnbr_fd(n, fd);
		}
	}
	else if (n < 10)
	{
		n += 48;
		write(fd, &n, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
/*
#include <stdio.h>

int	main(void)
{
	ft_putnbr_fd(-2147483648, 1);
}
*/
/*

----- Parameters -----

	n: The integer to output.
	fd: The file descriptor on which to write.

----- Return Value -----

	None.

----- External Functions -----

	write.

----- Description -----

	Outputs the integer ’n’ to the given file descriptor.

*/
