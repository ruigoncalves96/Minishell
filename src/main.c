/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2025/01/08 16:14:59 by randrade         ###   ########.fr       */
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
/*
	[X] pwd muda ao fazer cd
	[]  Mudar variavel ShellLVL

	[X] Unset
	[] export
*/
int main(int argc, char *argv[],char *envp[])
{
	t_builtins	builtins;
	t_prompt_info	prompt_info;
	t_list		*tokens;
	
	(void)argv;
	if (argc != 1)
	        return (1);
	welcome();
	init_variables_builtins(&builtins);
	ft_memset(&prompt_info, 0, sizeof(t_prompt_info));
	prompt_info.env = init_env(envp);
	if(!prompt_info.env)
	        return (1);
	while (1)
	{
		prompt_info.prompt = readline("Minishell> ");
		if(!prompt_info.prompt)
		{
			free_env(prompt_info.env);
			break;
		}
		if (prompt_info.prompt[0] != '\0')
			tokens = ft_parsing(&prompt_info);
		if(ft_strcmp(*tokens->str,"env") == 0)
			print_env_list(prompt_info.env);
		else if(ft_strcmp(*tokens->str,"pwd") == 0)
		    	pwd_builtin();
		else if(ft_strcmp(*tokens->str,"cd") == 0)
		    cd_builtin(NULL,prompt_info.env);
		else if(ft_strcmp(*tokens->str,"arr") == 0)
			handle_export(prompt_info.env);
		else if(ft_strcmp(*tokens->str,"export") == 0)
			export_env_var(prompt_info.env, tokens->str[1], tokens->str[2]);
		else if(ft_strcmp(*tokens->str,"unset") == 0)
			unset_env_var(prompt_info.env, tokens->str[1]);
		free(prompt_info.prompt);
		ft_free_list(tokens);
	}
	free_env(prompt_info.env);
	return 0;
}
