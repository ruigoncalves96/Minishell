/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:58:24 by randrade          #+#    #+#             */
/*   Updated: 2024/10/24 14:39:24 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int	ft_cleanbuf_gnl(char *str)
{
	int	check_nl;
	int	i;
	int	j;

	check_nl = 0;
	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
	{
		check_nl++;
		i++;
		while (str[i])
			str[j++] = str[i++];
	}
	while (j <= BUFFER_SIZE)
		str[j++] = '\0';
	return (check_nl);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	ptr = malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (free(s1), NULL);
	i = 0;
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	if (s1)
		free(s1);
	return (ptr);
}
