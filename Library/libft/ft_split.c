/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:30:48 by randrade          #+#    #+#             */
/*   Updated: 2024/05/01 14:33:43 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (((s[i + 1]) == c && s[i] != c) || ((s[i + 1]) == '\0' && s[i] != c))
			count++;
		i++;
	}
	return (count);
}

static int	ft_wrdlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*ft_wrdcpy(char const *s, char c, char **ptr)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		(*ptr)[i] = *s;
		i++;
		s++;
	}
	(*ptr)[i] = '\0';
	return ((char *)s);
}

static void	ft_free_alloc(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		count_words;
	int		wrd_len;
	int		i;

	count_words = ft_count_words(s, c);
	ptr = (char **) ft_calloc((count_words + 1), sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < count_words)
	{
		while (*s == c)
			s++;
		wrd_len = ft_wrdlen(s, c);
		ptr[i] = (char *) ft_calloc(wrd_len + 1, sizeof(char));
		if (ptr[i] == NULL)
		{
			ft_free_alloc(ptr);
			return (NULL);
		}
		s = ft_wrdcpy(s, c, &ptr[i]);
		i++;
	}
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*str = "  Free the duck!  ";
	char	c = ' ';
	char	**split_str = ft_split(str, c);
	int	i;


	i = 0;
	while (split_str[i])
	{
		printf("%s\n", split_str[i]);
		i++;
	}
	printf("%s\n", split_str[i]);

	i = 0;
	while (split_str[i])
	{
		free(split_str[i]);
		i++;
	}
	free(split_str[i]);

}
*/
/*

----- Parameters -----
	s: The string to be split.
	c: The delimiter character.

------ Return value -----

	The array of new strings resulting from the split.
	NULL if the allocation fails.

----- External functions -----

	malloc
	free

----- Description -----

	Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.

*/
