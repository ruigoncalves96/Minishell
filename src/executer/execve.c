#include "../../includes/minishell.h"

static void handle_execve_error(char *path,char **env_array,t_prompt_info prompt_info,t_token *token)
{
    ft_free_double_array(env_array);
    if (access(path, F_OK) != 0)
    {
        free(path);
        perror("access");
        close_fds();
        prompt_info.builtins->exit_code = 127;
        exit(127);
    }
    if (access(path, X_OK) != 0)
    {
        free(path);
        perror("access");
        close_fds();
        prompt_info.builtins->exit_code = 126;
        exit(126);
    }
    free(path);
    perror("execve");
    cleanup_all(&prompt_info,token);
    exit(1);
}

int executer_manager(char **str, t_env *env,t_prompt_info prompt_info,t_token *token)
{
	char *path;
	char **env_array;
	pid_t child;
	int status;

    path = get_command_path(*str,env);
    env_array = convert_env_to_array(env);
    if(!path)
    {
        prompt_info.builtins->exit_code = 127;
        ft_free_double_array(env_array);
        return (1);
    }
    child = fork();
    if(child == 0)
    {
   	    signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if(execve(path,str,env_array) == -1)
            handle_execve_error(path,env_array,prompt_info,token);
    }
    signal(SIGINT, SIG_IGN);
    waitpid(child,&status, 0);
    prompt_info.builtins->exit_code = get_exit_status(status);
    set_signals();
    free(path);
    ft_free_double_array(env_array);
    return (0);
}
