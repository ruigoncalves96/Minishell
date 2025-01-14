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
	[X] export

	[X] pwd nao esta a mudar no env
	[X] se colocarem export e um valor a frente ele nao aparece no env mas aparece no export ex(export cbum)
	[X] dar merge nas duas funçoes de export
	[X] fazer com que seja possivel dar export em mais que uma variavel seguida 

	[X] deixar a pessoa dar usent a mais que uma variavel
	[X] criar funcao que diga se e um builtin

	[] criar funcao que veja se o comando passado e um comando 
*/


static int execute_builtin(t_list *tokens, t_prompt_info prompt_info)
{
    if (!tokens || !tokens->str || !*tokens->str)
        return (0);

    if (!is_builtin(*tokens->str))
        return (0);

    if (ft_strcmp(*tokens->str, "env") == 0)
        print_env_list(prompt_info.env);
    else if (ft_strcmp(*tokens->str, "pwd") == 0)
        pwd_builtin();
    else if (ft_strcmp(*tokens->str, "cd") == 0)
        cd_manager(tokens->str, prompt_info.env);
    else if (ft_strcmp(*tokens->str, "export") == 0)
        export_manager(tokens->str, prompt_info.env);
    else if (ft_strcmp(*tokens->str, "unset") == 0)
        manager_unset(tokens->str, prompt_info.env);
    else if (ft_strcmp(*tokens->str, "echo") == 0)
        handle_echo(tokens->str);
	else if (ft_strcmp(*tokens->str, "exit") == 0)
		exit_manager(tokens->str);
    return (1);
}



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
		else
			tokens = ft_parsing(&prompt_info);
		if(tokens)
		{
		if(execute_builtin(tokens,prompt_info) == 0)//Comando externo
		{
			loop_executer(tokens,prompt_info.env);
		
		}
		free(prompt_info.prompt);
		ft_free_list(tokens);
		}
	}
	free_env(prompt_info.env);
	return 0;
}
