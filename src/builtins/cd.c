#include "../../includes/minishell.h"

/*
    ao fazer cd sem argumentos vou para a home
*/
static int create_pwd(char **pwd)
{
    *pwd = getcwd(NULL,0);
    if(!pwd)
    {
        perror("cd: getcwd error");
        return -1;
    }
    return 0;
}

static int handle_cd_alone(char **path)
{
    if(*path == NULL)
    {
        *path = getenv("HOME");
        if(!*path)
        {
            ft_putstr_fd("Fodeu apagaram o HOME", 2);
            return -1;
        }
    }
    return 0;
}
int cd_builtin(char *path,t_env *env)
{
    char *pwd;
    char *old_pwd;

    if(create_pwd(&old_pwd) == -1)
        return -1;

    if(ft_strcmp(env->vars->key,"OLDPWD") == 0) // Proteçao caso apagem o OLDPWD ele ja nao vai voltar a ser crido
        export_env_var(env,"OLDPWD",old_pwd,0);

    if(handle_cd_alone(&path) == -1)
        return(free(old_pwd),-1);

    if(chdir(path) == -1)
    {
        perror("cd");
        return (free(old_pwd),-1);
    }

    if(create_pwd(&pwd) == -1)
          return (free(old_pwd), -1);

    if(ft_strcmp(env->vars->key,"PWD") == 0)
        export_env_var(env,"PWD",pwd,0);

    free(old_pwd);
    free(pwd);
    return 0;
}
