/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2025/03/28 15:03:05 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_control_c_code(t_prompt_info prompt_info)
{
	if (g_heredoc_c_pressed)
	{
		prompt_info.builtins->exit_code = 130;
		g_heredoc_c_pressed = 0;
	}
}

static void	shell_loop(t_prompt_info prompt_info)
{
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		prompt_info.prompt = readline("Minishell> ");
		check_control_c_code(prompt_info);
		if (!prompt_info.prompt)
		{
			cleanup_all(&prompt_info, NULL);
			break ;
		}
		if (prompt_info.prompt[0] != '\0')
		{
			add_history(prompt_info.prompt);
			tokens = parsing(&prompt_info);
			if (tokens)
			{
				loop_executer(tokens, prompt_info);
				free_token_tree(tokens);
				tokens = NULL;
			}
		}
		free(prompt_info.prompt);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_builtins		builtins;
	t_prompt_info	prompt_info;

	(void)argv;
	if (argc != 1)
		return (1);
	set_signals();
	init_variables_builtins(&builtins);
	ft_memset(&prompt_info, 0, sizeof(t_prompt_info));
	prompt_info.env = init_env(envp);
	prompt_info.builtins = &builtins;
	if (!prompt_info.env)
		return (1);
	shell_loop(prompt_info);
	return (0);
}
