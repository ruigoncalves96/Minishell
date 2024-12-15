/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2024/12/10 13:22:59 by randrade         ###   ########.fr       */
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
    welcome();
    
    t_builtins builtins;

    init_variables_builtins(&builtins);
    (void) argc;
    (void) argv;
    char **minishell_envp;
    char *prompt;

    minishell_envp = copy_envp(envp);
    if(!minishell_envp)
        return (-1);

    while (1)
    {
        prompt = readline("Minishell> ");
        if(!prompt)
        {
            free_double_array(minishell_envp);
            break;
        }
        if(ft_strncmp(prompt,"env",3) == 0)
            ft_print_double_array(minishell_envp);
        else if(ft_strncmp(prompt,"pwd",3) == 0)
            pwd_builtin();
        else if(ft_strncmp(prompt,"cd",2) == 0)
            cd_builtin(prompt);
        free(prompt);
    }
    

    free_double_array(minishell_envp);
    return 0;
}




