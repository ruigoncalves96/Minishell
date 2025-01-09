#include "../../includes/minishell.h"

/*
    ao fazer cd sem argumentos vou para a home
*/

void cd_builtin(char *path,t_env *env)
{
    //Nao tenho PATH VOU PARA A Home
    if(path ==  NULL)
    {
        path = getenv("HOME"); 
        if(!path)
            ft_putstr_fd("Fodeu apagaram o HOME",2);
    }
    char *pwd;
    
    pwd = getcwd(NULL,0);
    if(pwd == NULL)
        return;
    if(ft_strcmp(env->vars->key,"PWD") == 0)
        export_env_var(env,"PWD",pwd);
    //Vou mudar para o diretorio passado
    if(chdir(path) == -1)
        perror("cd");
    
}
