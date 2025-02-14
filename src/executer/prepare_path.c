#include "../../includes/minishell.h"

/*
   [X] Conseguir o path dentro da minha linked list e returnar o value dele
   [X] Separar o conteudo do PATH(com :)
   [X] juntar o caminho dado para formar caminho absoluto /bin/ + /ls
   [X] usar funcao access para verificar se o comando e executavel
*/

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
/// @brief  Joins directory with comand name and add /
/// @param dir_path
/// @param command
/// @return
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
/// @brief Search for comand in every path directory
/// @param split_path
/// @param command
/// @return Return the path of the comand
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
        if (access(full_path, X_OK) == 0)
        {
            command_path = full_path;
            break;
        }
        free(full_path);
        i++;
    }
    return (command_path);
}
/// @brief
/// @param command
/// @param env
/// @return path of comand
char *get_command_path(char *command, t_env *env)
{
    char *path;
    char **split_path;
    char *command_path;
    if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
    {
        if (access(command, X_OK) == 0)
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
/// @brief
/// @param command
/// @param prompt_info
/// @return 0 if command exists, -1 command don't exist
int validate_command_path(char *command, t_env *env)
{
    char *command_path;

    command_path = get_command_path(command, env);
    if (!command_path || command[0] == '\0')
    {
        ft_putstr_fd("Command not found: ", 2);
        ft_putstr_fd(command,2);
        ft_putstr_fd("\n",2);
        return (-1);
    }
    //printf("Command found: %s\n", command_path);
    free(command_path);
    return (0);
}
