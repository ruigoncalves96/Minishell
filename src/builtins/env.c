#include "../../includes/minishell.h"


char **copy_envp(char *envp[])
{
    int i;
    char **minishell_envp;

    i = 0;
    while (envp[i])
        i++;
    minishell_envp = malloc((i + 1) * sizeof(char *));
    if (minishell_envp == NULL)
        return NULL;
    i = 0;
    while (envp[i])
    {
        minishell_envp[i] = ft_strdup(envp[i]);
        if (minishell_envp[i] == NULL)
        {
            free_double_array(minishell_envp);
            return NULL;
        }
        i++;
    }
    minishell_envp[i] = NULL;
    return minishell_envp;
}

void flag_env()
{
    char *pwd;
    char **flag_env;


    flag_env = malloc(sizeof(char *) * 4);
    if (!flag_env)
        return;
    pwd = getcwd(NULL, 0); 
    if(pwd == NULL)
    {
        printf("Deu erro dentro da funcao flag_env guardar o pwd");
        return;
    }
    flag_env[0] = ft_strdup(pwd);
    free(pwd);
    flag_env[1] = ft_strdup("SHLVL=1");
    flag_env[2] = ft_strdup("_=/usr/bin/env");
    flag_env[3] = NULL;
    ft_print_double_array(flag_env);
    free_double_array(flag_env);
}

/// @brief Function will print env
/// @param builtins Builtins Struct
///@param flag True will print env with flag(-i),False will print normal env
void print_env(char *env[],bool flag)
{
    if(flag == true)
    {
        flag_env();
    }
    else
        ft_print_double_array(env);
}