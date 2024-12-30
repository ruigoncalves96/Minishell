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

static void init_variables_builtins(t_builtins *builtins, char *envp[])
{
    builtins->exit_status = 0;
    builtins->echo_flag = true;
    builtins->minishell_env = copy_envp(envp);
    builtins->export_env = copy_envp(envp);
}
int main(int argc,char *argv[],char *envp[])
{
    (void)argc;
    (void)argv;
    t_builtins vars;
    init_variables_builtins(&vars, envp);
    int i;
    char *key1;
  // char *key1 = get_key();
    i = 0;
    while (vars.minishell_env[i])
     {
        key1 = get_key(vars.minishell_env[i]);
        if(ft_strcmp(key1,"HOME=") != 0)
        {
            //A minha key nao e igual a nehuma ou seja eu nao existo
            printf("Eu nao existo");
        }else
        {
            //Encontrei um key value igual ao meu eu existo
            printf("Eu existo");
        }
        i++;
    }
    
}
/* 
// Mensagem de boas-vindas
static void welcome(void)
{
    printf("   __  __  _       _     _         _ _ \n");
    printf("  |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
    printf("  | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
    printf("  | |  | | | | | | \\__ \\ | | |  __/ | |\n");
    printf("  |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n");
}

// Inicializa a estrutura t_builtins

Int main para testar ENV -I || EXPORT
int main(int argc, char *argv[], char *env[])
{
    (void)argc;
    (void)argv;

    flag_env();
    welcome();

    // Inicializa a estrutura
    t_builtins vars;
    init_variables_builtins(&vars, env);

    // Lida com o comando individual export
    handle_export(vars.export_env);

    // Libera memória alocada
    free_double_array(vars.minishell_env);
    free_double_array(vars.export_env);

    return 0;
}

*/
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

/*
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
*/




