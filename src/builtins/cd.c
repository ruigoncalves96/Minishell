#include "../../includes/minishell.h"

/*
    ao fazer cd sem argumentos vou para a home
*/

void cd_builtin(char *path)
{
    //Nao tenho PATH VOU PARA A Home
    if(path ==  NULL)
    {
        path = getenv("HOME"); 
        if(!path)
        {
            ft_putstr_fd("Fodeu apagaram o HOME",2);
        }
    }

    //Vou mudar para o diretorio passado
    if(chdir(path) == -1)
    {
        perror("cd");
    }
}