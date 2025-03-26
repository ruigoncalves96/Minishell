#include "../../includes/minishell.h"

static void write_heredoc(t_token *token, int pipes[2])
{
    int     i;

    i = 0;
    close(pipes[0]);
    while (token->red->heredoc[i])
    {
        ft_putstr_fd(token->red->heredoc[i], pipes[1]);
        i++;
    }
}

void    heredoc_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int     pipes[2];
    int status;

    if (token->red->fd == -4 || !get_heredoc_command_tree(token))
        runcmd(token->previous, env, prompt_info);
    if (pipe(pipes) == -1)
        return;
    if (fork() == 0)
    {
        write_heredoc(token, pipes);
        cleanup_all(&prompt_info,token);
        exit(0);
    }
    wait(&status);
    if (fork() == 0)
    {
        dup2(pipes[0], STDIN_FILENO);
        close_pipes(pipes);
        runcmd(token->previous, env, prompt_info);
        cleanup_all(&prompt_info,token);
        exit(0);
    }
    close_pipes(pipes);
    wait(&status);
    prompt_info.builtins->exit_code = get_exit_status(status);
}
