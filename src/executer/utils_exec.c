#include "../../includes/minishell.h"

t_token    *get_heredoc_command_tree(t_token *token)
{
    while (token->previous && token->previous->red)
            token = token->previous;
    if (token->previous && token->previous->type == COMMAND)
        return (token->previous);
    return (NULL);
}

t_token    *get_heredoc_command_list(t_token *token)
{
    while (token->previous && token->previous->previous && token->previous->previous->red)
        token = token->previous->previous;
    if (token->previous && token->previous->type == COMMAND)
        return (token->previous);
    return (NULL);
}

void close_pipes(int pipes[2])
{
    close(pipes[0]);
    close(pipes[1]);
}

int get_exit_status(int status)
{
    int signal_num;

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        signal_num = WTERMSIG(status);
        if (signal_num == SIGINT)
            return 130;
        else if (signal_num == SIGQUIT)
            return 131;
        else
            return 128 + signal_num;
    }
    else
        return 1;
}
