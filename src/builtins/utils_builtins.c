/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:51:57 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/24 12:51:59 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Print a error message
/// @param cmd COMAND USED
/// @param arg ARGUMENT FOR THE COMAND (PASS NULL TO IGNORE)
/// @param msg MESSAGE ERROR
void	print_error(const char *cmd, const char *arg, const char *msg,
		bool print_bash)
{
	if (print_bash)
		ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		if (arg[0] == '\0')
			ft_putstr_fd("'' ", 2);
		else
			ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
}

char	*get_key(char *env)
{
	int		len;
	char	*key;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = ft_calloc(len + 1, 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, env, len + 1);
	return (key);
}

char	*get_value(char *env_str)
{
	char	*equals;

	equals = ft_strchr(env_str, '=');
	if (!equals)
		return (NULL);
	return (ft_strdup(equals + 1));
}

char	*get_env_value(t_env *env, const char *key)
{
	t_env_var	*current;

	if (!env || !key)
		return (NULL);
	current = env->vars;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
