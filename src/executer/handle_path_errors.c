#include "../../includes/minishell.h"

static int is_directory(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return 0;  // Error
    }
    return S_ISDIR(path_stat.st_mode); // Check if it's a directory
}
static int handle_dot_commands(char *command)
{
    if (command[0] == '.' && (command[1] == '\0' || 
        (command[1] == '.' && command[2] == '\0')))
    {
        print_error(NULL, command, COMMAND_NOT_FOUND, false);
        return (127);
    }
    return (0);
}

static int handle_path_errors(char *command, char *command_path)
{
    if (!command_path)
    {
        if (command[0] == '.' || command[0] == '/')
            print_error(NULL, command, NO_FILE_OR_DIRECTORY, false);
        else
            print_error(NULL, command, COMMAND_NOT_FOUND, false);
        return (127);
    }
    return (0);
}

static int check_permissions(char *command, char *command_path)
{
    if (is_directory(command_path))
    {
        print_error(NULL, command, DIRECTORY, true);
        free(command_path);
        return (126);
    }
    
    if(access(command_path, X_OK) != 0)
    {
        print_error(NULL, command, PERMISSION_DENIED, true);
        free(command_path);
        return (126);
    }
    return (0);
}

int validate_command_path(char *command, t_env *env)
{
    char *command_path;
    int status;
    
    status = handle_dot_commands(command);
    if (status != 0)
        return (status);
    
    command_path = get_command_path(command, env);
    
    status = handle_path_errors(command, command_path);
    if (status != 0)
        return (status);
        
    status = check_permissions(command, command_path);
    if (status != 0)
        return (status);
    
    free(command_path);
    return (0);
}
