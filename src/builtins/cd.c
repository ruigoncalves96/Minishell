#include "../../includes/minishell.h"

/*
    ao fazer cd sem argumentos vou para a home
*/

int cd_builtin(char *path,t_env *env)
{
    char *pwd;
    char *old_pwd;
    old_pwd = getcwd(NULL,0);
    if(!old_pwd)
    {
        perror("cd: getcwd error");
        return -1;
    }

     if(ft_strcmp(env->vars->key,"OLDPWD") == 0)
        export_env_var(env,"OLDPWD",old_pwd);

    //cd sem argumentos
    if(path ==  NULL)
    {
        path = getenv("HOME"); 
        if(!path)
        {
            ft_putstr_fd("Fodeu apagaram o HOME",2);
            free(old_pwd);
            return -1;
        }
    }
        //Vou mudar para o diretorio passado
    if(chdir(path) == -1)
    {
        perror("cd");
        free(old_pwd);
        return -1;
    }

    pwd = getcwd(NULL,0);
    if(!pwd)
    {
        perror("cd: getcwd error");
        free(old_pwd);
        return -1;
    }

    if(ft_strcmp(env->vars->key,"PWD") == 0)
        export_env_var(env,"PWD",pwd);
    free(old_pwd);
    free(pwd);
    return 0;
}
