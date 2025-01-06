#include "../../includes/minishell.h"

void init_variables_builtins(t_builtins *builtins, char *env[])
{
    builtins->exit_status = 0;
    builtins->echo_flag = true;
    builtins->minishell_env = copy_envp(env);
    builtins->export_env = copy_envp(env);
}

/// @brief Function will free all the memory allocated initializing the variables
/// @param builtins 
void free_variables_builtins(t_builtins *vars)
{
        free_double_array(vars->minishell_env);
        free_double_array(vars->export_env);
}