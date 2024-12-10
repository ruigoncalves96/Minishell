/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:58:51 by randrade          #+#    #+#             */
/*   Updated: 2024/10/24 14:39:14 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*new_line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = NULL;
	buffer[fd][BUFFER_SIZE] = '\0';
	if (!buffer[fd][0])
	{
		if (read(fd, buffer[fd], BUFFER_SIZE) < 0)
			return (NULL);
	}
	while (buffer[fd][0])
	{
		new_line = ft_strjoin_gnl(new_line, buffer[fd]);
		if (!new_line)
			return (NULL);
		if (ft_cleanbuf_gnl(buffer[fd]) == 1)
			break ;
		if (read(fd, buffer[fd], BUFFER_SIZE) < 0)
			return (free(new_line), NULL);
	}
	return (new_line);
}
