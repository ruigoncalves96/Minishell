/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2025/01/17 17:39:13 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void welcome(void)
{
    printf("   __  __  _       _     _         _ _ \n");
    printf("  |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
    printf("  | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
    printf("  | |  | | | | | | \\__ \\ | | |  __/ | |\n");
    printf("  |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n");
}

static void shell_loop(t_prompt_info prompt_info)
{
    t_token		*tokens;

	tokens = NULL;
	while (1)
	{
		prompt_info.prompt = readline("Minishell> ");
		if(!prompt_info.prompt)
			break;
		if (prompt_info.prompt[0] != '\0')
		{
		    add_history(prompt_info.prompt);
		    tokens = ft_parsing(&prompt_info);
			if (tokens)
			{
			    loop_executer(&tokens, prompt_info.env, prompt_info);
				ft_free_token_list(tokens);
			}
		}
		free(prompt_info.prompt);
	}
}

int main(int argc, char *argv[],char *envp[])
{
	t_builtins	builtins;
	t_prompt_info	prompt_info;

	(void)argv;
	if (argc != 1)
	        return (1);
	welcome();
	set_signals();
	init_variables_builtins(&builtins);
	ft_memset(&prompt_info, 0, sizeof(t_prompt_info));
	prompt_info.env = init_env(envp);
	if(!prompt_info.env)
	        return (1);
	update_shlvl(prompt_info.env);
	shell_loop(prompt_info);
	free_env(prompt_info.env);
	rl_clear_history();
	return 0;
}
