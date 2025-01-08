#include "../../includes/minishell.h"

void init_variables_builtins(t_builtins *builtins)
{
    builtins->exit_status = 0;
    builtins->echo_flag = true;
    //builtins->minishell_env = copy_envp(env);
    //builtins->export_env = copy_envp(env);
}
