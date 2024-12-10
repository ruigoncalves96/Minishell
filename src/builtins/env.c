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
    
    //So falta copiar 
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
