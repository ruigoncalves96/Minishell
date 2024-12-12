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