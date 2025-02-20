/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2025/02/20 11:18:14 by hguerrei         ###   ########.fr       */
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

int main(int argc, char *argv[],char *envp[])
{
	t_builtins	builtins;
	t_prompt_info	prompt_info;
	t_token		*tokens;

	(void)argv;
	if (argc != 1)
	        return (1);
	welcome();
	init_variables_builtins(&builtins);
	ft_memset(&prompt_info, 0, sizeof(t_prompt_info));
	prompt_info.env = init_env(envp);
	if(!prompt_info.env)
	        return (1);
	update_shlvl(prompt_info.env);
	while (1)
{
    prompt_info.prompt = readline("Minishell> ");
    if (!prompt_info.prompt)
    {
        break;
    }
    else
        tokens = ft_parsing(&prompt_info);
    if (prompt_info.prompt[0] != '\0')
        add_history(prompt_info.prompt);
    if (tokens)
    {
        loop_executer(tokens, prompt_info.env, prompt_info, &builtins);
    }
    free(prompt_info.prompt);
    ft_free_token_list(tokens);
}

	free_env(prompt_info.env);
	rl_clear_history();
	return 0;
}
