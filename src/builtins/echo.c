/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:04:01 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/24 12:05:08 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo(char **arr, bool echo_flag)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" ");
		i++;
	}
	if (echo_flag == false)
		printf("\n");
}

static bool	is_valid_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (i > 1);
}

void	handle_echo(char *argv[])
{
	t_builtins	vars;
	int			start;

	vars.echo_flag = false;
	start = 1;
	if (argv[1])
	{
		while (argv[start] && is_valid_n_flag(argv[start]))
		{
			vars.echo_flag = true;
			start++;
			if (!argv[start])
				break ;
		}
	}
	echo(&argv[start], vars.echo_flag);
}
