#include "../../includes/minishell.h"

/*
   [X] Conseguir o path dentro da minha linked list e returnar o value dele
   [X] Separar o conteudo do PATH(com :)
   [X] juntar o caminho dado para formar caminho absoluto /bin/ + /ls
   [X] usar funcao access para verificar se o comando e executavel
*/

static int is_directory(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return 0;  // Error
    }
    return S_ISDIR(path_stat.st_mode); // Check if it's a directory
}


///@return funcao vai returnar value de uma variavel existente no sistema
char *get_env_value(t_env *env,const char *key)
{
    t_env_var *current;
    if(!env || !key)
        return (NULL);

    current = env->vars;
    while (current)
    {
        if(ft_strcmp(current->key,key) == 0)
            return(current->value);
        current = current->next;
    }
    return (NULL);
}

static char *join_command_path(char *dir_path, char *command)
{
    char *temp_path;
    char *full_path;

    temp_path = ft_strjoin(dir_path, "/");
    if (!temp_path)
        return (NULL);
    full_path = ft_strjoin(temp_path, command);
    free(temp_path);
    return (full_path);
}

static char *search_in_path_dirs(char **split_path, char *command)
{
    int i;
    char *full_path;
    char *command_path;

    i = 0;
    command_path = NULL;
    while (split_path[i])
    {
        full_path = join_command_path(split_path[i], command);
        if (!full_path)
            return (NULL);
        if (access(full_path, F_OK) == 0)
        {
            command_path = full_path;
            break;
        }
        free(full_path);
        i++;
    }
    return (command_path);
}

char *get_command_path(char *command, t_env *env)
{
    char *path;
    char **split_path;
    char *command_path;
    if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
    {
        if (access(command, F_OK) == 0)
            return (ft_strdup(command));
        return (NULL);
    }
    path = get_env_value(env, "PATH");
    if (!path)
        return (NULL);
    split_path = ft_split(path, ':');
    if (!split_path)
        return (NULL);
    command_path = search_in_path_dirs(split_path, command);
    ft_free_double_array(split_path);
    return (command_path);
}

int validate_command_path(char *command, t_env *env)
{
    char *command_path;

    if (command[0] == '.' && (command[1] == '\0' || (command[1] == '.' && command[2] == '\0')))
    {
        print_error(NULL, command, COMMAND_NOT_FOUND, false);
        return (127);
    }
    command_path = get_command_path(command, env);
    if (!command_path)
    {
        print_error(NULL, command, COMMAND_NOT_FOUND, false);
        return (127);
    }
    if (is_directory(command_path))
    {
        print_error(NULL, command, DIRECTORY, true);
        free(command_path);
        return (126);
    }
    if(access(command_path,X_OK) != 0) //Checo se tenho permissoes safadas
    {
        print_error(NULL,command,PERMISSION_DENIED,true);
        free(command_path);
        return(126);
    }
    free(command_path);
    return (0);
}
