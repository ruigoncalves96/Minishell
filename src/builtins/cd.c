#include "../../includes/minishell.h"

/*
    [X] cd sem argumentos deve ir para a home
    [X] se o argumento do cd existir deve ir para a pasta
    [X] se ele navegar para o diretorio tenho de alterar as variaveis dentro do env (PWD OLDPWD)
    []  Falta so fazer proteçoes para as variaveis (PWD e OLDPWD)
*/

static int create_pwd(char **pwd)
{
    *pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        perror("cd: getcwd error");
        return (-1);
    }
    return (0);
}

static int validate_arguments(char **str)
{
    if (array_size(str) > 3)
    {
        ft_putstr_fd("cd: too many arguments", 2);
        return (-1);
    }
    return (0);
}

static char *get_target_path(char *path)
{
    if (path == NULL)
    {
        path = getenv("HOME");
        if (!path)
        {
            ft_putstr_fd("cd: HOME not set", 2);
            return (NULL);
        }
    }
    return (path);
}

static int update_pwd_vars(t_env *env, char *old_pwd)
{
    char *new_pwd;

    if (create_pwd(&new_pwd) == -1)
        return (-1);

    export_env_var(env, "OLDPWD", old_pwd, 0);
    export_env_var(env, "PWD", new_pwd, 0);
    free(new_pwd);
    return (0);
}

int cd_manager(char **str, t_env *env)
{
    char *old_pwd;
    char *path;

    if (validate_arguments(str) == -1)
        return (-1);
    if (create_pwd(&old_pwd) == -1)
        return (-1);

    path = get_target_path(str[1]);
    if (!path)
        return (free(old_pwd), -1);

    if (chdir(path) == -1)
    {
        perror("cd");
        return (free(old_pwd), -1);
    }

    if (update_pwd_vars(env, old_pwd) == -1)
        return (free(old_pwd), -1);

    free(old_pwd);
    return (0);
}
