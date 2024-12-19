/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2024/12/19 16:31:19 by randrade         ###   ########.fr       */
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


static void init_variables_builtins(t_builtins *builtins)
{
    builtins->exit_status = 0;
    builtins->echo_flag = true;
}
/*

int main(int argc,char *argv[])
{

    if(argc < 2)
        return 1;
    
    t_builtins vars;
    init_variables_builtins(&vars);
    
    if(strncmp(argv[1],"echo",4) == 0)
        handle_echo(argc,argv);
    return 0;
}


Codigo teste do exit
int main(void)

{
    t_builtins builtins;

    init_variables_builtins(&builtins);
    welcome();

    char *args4[] = {"exit", "OLAADASF", NULL};

    create_exit_code(&builtins, args4);
    printf("Exit status: %ld\n", builtins.exit_status);
    exit(builtins.exit_status);
 
    return 0;
}
*/


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
	ft_parsing(&prompt_info);
        if(ft_strncmp(prompt_info.prompt,"env",3) == 0)
            ft_print_double_array(prompt_info.env);
        else if(ft_strncmp(prompt_info.prompt,"pwd",3) == 0)
            pwd_builtin();
        else if(ft_strncmp(prompt_info.prompt,"cd",2) == 0)
            cd_builtin(prompt_info.prompt);
        free(prompt_info.prompt);
    }
    free_double_array(prompt_info.env);
    return 0;
}




