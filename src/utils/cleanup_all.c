/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:18:47 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/28 15:19:35 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_all(t_prompt_info *prompt_info, t_token *tokens)
{
	rl_clear_history();
	if (prompt_info->prompt)
	{
		free(prompt_info->prompt);
		prompt_info->prompt = NULL;
	}
	if (tokens)
		free_token_tree(go_to_tree_top(tokens));
	if (prompt_info->env)
	{
		free_env(prompt_info->env);
		prompt_info->env = NULL;
	}
	close_fds();
}

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}

void	init_variables_builtins(t_builtins *builtins)
{
	builtins->echo_flag = true;
	builtins->exit_code = 0;
}
