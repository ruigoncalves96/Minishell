/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:03 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 12:45:09 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	ft_putstr_fd("Free the ducks!\n", 1);
}
*/
/*

----- Parameters -----

	s: The string to output.
	fd: The file descriptor on which to write.

----- Return Value -----

	None.

----- External Functs -----

	write.

----- Description -----

	Outputs the string ’s’ to the given file descriptor.

*/
