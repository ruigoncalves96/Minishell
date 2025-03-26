/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2025/03/19 15:48:10 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static void welcome(void)
{
    printf("   __  __  _       _     _         _ _ \n");
    printf("  |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
    printf("  | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
    printf("  | |  | | | | | | \\__ \\ | | |  __/ | |\n");
    printf("  |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n");
}
*/

static void shell_loop(t_prompt_info prompt_info)
{
    t_token		*tokens;

	tokens = NULL;
	while (1)
	{
		prompt_info.prompt = readline("Minishell> ");
		if(g_heredoc_c_pressed)
		{
			prompt_info.builtins->exit_code = 130;
			g_heredoc_c_pressed = 0;
		}
		if(!prompt_info.prompt)
		{
			cleanup_all(&prompt_info, NULL);
			break;
		}
		if (prompt_info.prompt[0] != '\0')
		{
		    add_history(prompt_info.prompt);
		    tokens = parsing(&prompt_info);
			if (tokens)
			{
			    loop_executer(tokens, prompt_info.env, prompt_info);
				free_token_tree(tokens);
				tokens = NULL;
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
	//welcome();
	set_signals();
	init_variables_builtins(&builtins);
	ft_memset(&prompt_info, 0, sizeof(t_prompt_info));
	prompt_info.env = init_env(envp);
	prompt_info.builtins = &builtins;
	if(!prompt_info.env)
	        return (1);
	//update_shlvl(prompt_info.env);
	shell_loop(prompt_info);
	return 0;
}
