/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:29:01 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 15:51:54 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		str_len;
	int		i;

	str_len = ft_strlen(s);
	ptr = ft_calloc(str_len + 1, sizeof(char));
	if (ptr == NULL)
		return (ptr);
	i = 0;
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
}
*/
/*

----- Parameters -----

	s: The string on which to iterate.
	f: The function to apply to each character.

----- Return Value -----

	The string created from the successive applications of ’f’.
	Returns NULL if the allocation fails.

----- External functs. -----

	Malloc.

----- Description -----

	Applies the function f to each character of the
string s, passing its index as the first argument
and the character itself as the second. A new
string is created (using malloc(3)) to collect the
results from the successive applications of f.

*/
