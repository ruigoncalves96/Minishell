/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2025/01/08 14:20:49 by randrade         ###   ########.fr       */
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
	
	(void)argv;
	if (argc != 1)
	        return (1);
	welcome();
	init_variables_builtins(&builtins);
	ft_memset(&prompt_info, 0, sizeof(t_prompt_info));
	prompt_info.env = copy_envp(envp);
	if(!prompt_info.env)
	        return (1);
	while (1)
	{
		prompt_info.prompt = readline("Minishell> ");
		if(!prompt_info.prompt)
		{
			free_double_array(prompt_info.env);
			break;
		}
		if (prompt_info.prompt[0] != '\0')
			ft_parsing(&prompt_info);
/*		if(ft_strncmp(prompt_info.prompt,"env",3) == 0)
		    ft_print_double_array(prompt_info.env);
		else if(ft_strncmp(prompt_info.prompt,"pwd",3) == 0)
		    pwd_builtin();
		else if(ft_strncmp(prompt_info.prompt,"cd",2) == 0)
		    cd_builtin(prompt_info.prompt);
*/		free(prompt_info.prompt);
	}
	free_double_array(prompt_info.env);
	return 0;
}
