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
int main(int argc, char *argv[],char *envp[])
{
    welcome();
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
      //  printf("Prompt: %s\n", prompt);
        if(ft_strncmp(prompt,"env",3) == 0)
            ft_print_double_array(minishell_envp);
        free(prompt);
    }
    

    free_double_array(minishell_envp);
    return 0;
}


