/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:49:28 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 12:53:13 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
	write(fd, "\n", 1);
}
/*
#include <stdio.h>

int	main(void)
{
	ft_putendl_fd("Free the ducks!", 1);
}
*/
/*

----- Parameters -----

	s: The string to output.
	fd: The file descriptor on which to write.

----- Return Value -----

	None.

----- External Functs -----

	write

----- Description -----

	Outputs the string ’s’ to the given file descriptor followed by
       	a newline.

*/
