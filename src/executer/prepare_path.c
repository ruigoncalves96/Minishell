/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:52:13 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/24 12:52:15 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_command_path(char *dir_path, char *command)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(dir_path, "/");
	if (!temp_path)
		return (NULL);
	full_path = ft_strjoin(temp_path, command);
	free(temp_path);
	return (full_path);
}

static char	*search_in_path_dirs(char **split_path, char *command)
{
	int		i;
	char	*full_path;
	char	*command_path;

	i = 0;
	command_path = NULL;
	while (split_path[i])
	{
		full_path = join_command_path(split_path[i], command);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
		{
			command_path = full_path;
			break ;
		}
		free(full_path);
		i++;
	}
	return (command_path);
}

char	*get_command_path(char *command, t_env *env)
{
	char	*path;
	char	**split_path;
	char	*command_path;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	path = get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	command_path = search_in_path_dirs(split_path, command);
	ft_free_double_array(split_path);
	return (command_path);
}
