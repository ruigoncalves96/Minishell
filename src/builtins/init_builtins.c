#include "../../includes/minishell.h"

void init_variables_builtins(t_builtins *builtins)
{
    builtins->echo_flag = true;
}
int is_builtin(char *cmd)
{
    const char *builtins[] = {"pwd", "echo", "env", "cd", "export", "unset", "exit", NULL};
    int i;

    i = 0;
    while (builtins[i])
    {
        if (ft_strcmp(cmd, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}