/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:16 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 12:37:03 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <stdio.h>

int	main(void)
{
	ft_putchar_fd('a', 1);
}
*/
/*

----- Parameters -----

	c: The character to output.
	fd: The file descriptor on which to write.

----- Return Value -----

	None.

----- Write -----

	write.

----- Description -----

	Outputs the character ’c’ to the given file descriptor.

*/
