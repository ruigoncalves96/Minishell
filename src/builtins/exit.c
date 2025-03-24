/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:08:02 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/24 12:08:04 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_digit(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	free_error_exit(char **args, t_builtins *builtins,
		t_prompt_info *prompt_info, t_token *tokens)
{
	print_error("exit", args[1], EXIT_NUMERIC_ERROR, true);
	builtins->exit_code = 2;
	cleanup_all(prompt_info, tokens);
	exit(2);
}

static void	handle_basic_exit(t_builtins *builtins, t_prompt_info *prompt_info,
		t_token *tokens)
{
	builtins->exit_code = 0;
	cleanup_all(prompt_info, tokens);
	exit(0);
}

void	exit_manager(char **args, t_builtins *builtins,
		t_prompt_info *prompt_info, t_token *tokens)
{
	long	num;

	num = 0;
	printf("exit\n");
	if (array_size(args) == 1)
	{
		handle_basic_exit(builtins, prompt_info, tokens);
	}
	if (!check_digit(args[1]))
		free_error_exit(args, builtins, prompt_info, tokens);
	if (array_size(args) > 2)
	{
		print_error("exit", NULL, TOO_MANY_ARGS, true);
		builtins->exit_code = 1;
		return ;
	}
	if (!ft_atol(args[1], &num))
		free_error_exit(args, builtins, prompt_info, tokens);
	num %= 256;
	if (num < 0)
		num += 256;
	builtins->exit_code = (int)num;
	cleanup_all(prompt_info, tokens);
	exit((int)num);
}
