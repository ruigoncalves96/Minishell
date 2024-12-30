#include "../../includes/minishell.h"


char **copy_envp(char *envp[])
{
    int i;
    char **minishell_envp;

    //Estou a contar o numero de variaveis de ambiente
    i = 0;
    while (envp[i])
        i++;
    
    //Ja tenho o tamanho vou alocar a memoria
    minishell_envp = malloc((i + 1) * sizeof(char *));
    if(minishell_envp == NULL)
        return NULL;
    
    //Vou copiar ennv
    i = 0;
    while (envp[i])
    {
        minishell_envp[i] = ft_strdup(envp[i]);
        if(!minishell_envp)
        {
            free_double_array(minishell_envp);
            return NULL;
        }
        i++;
    }
    minishell_envp[i] = NULL;
    return (minishell_envp);
}

void flag_env()
{
    char *pwd;
    char *flag_env[4];

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
}

//Vou dar return em um double point char com o env -i ja colocado la
/*
    Ao fazer o env -i este e o que deve la estar
    PWD=/home/redgtxt
    SHLVL=1
    _=/usr/bin/env
*/
/*
void  builtin_env(char *envp[],char *argv[])
{
   char **minishell_envp;
   
    if(ft_strncmp(argv[0],"env",3) == 0)
    {
        if(ft_strncmp(argv[1],"-i",2) == 0)
        {   
            minishell_envp = malloc(sizeof(char *));
            if(!minishell_envp)
                return NULL;
            minishell_envp[0] == NULL;
            ft_print_double_array(minishell_envp);
            free(minishell_envp);
        }else{
            //env
             minishell_envp = copy_envp(envp);
             ft_print_double_array(minishell_envp);
             free_double_array(minishell_envp);
        }
    }
}
*/