#include "../../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

static void get_heredoc_input(t_token *token, int pipes[2])
{
    char    *heredoc;

    heredoc = NULL;
    while (1)
    {
        heredoc = readline("> ");
        if (!heredoc)
        {
            close(pipes[0]);
            close(pipes[1]);
            exit (1);
        }
        if (ft_strncmp(heredoc, token->red->filename[0], ft_strlen((const char*)heredoc)) == 0)
        {
            free(heredoc);
            close(pipes[1]);
            return ;
        }
        if (token->red->filename[1] == NULL || token->red->fd == -1)
        {
            ft_putstr_fd(heredoc, pipes[1]);
            ft_putstr_fd("\n", pipes[1]);
        }
        free(heredoc);
    }
}

void    heredoc_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int     pipes[2];

    pipe(pipes);
    if (fork() == 0)
    {
        close(pipes[0]);
        get_heredoc_input(token, pipes);
        exit(0);
    }
    wait(NULL);
    if (fork() == 0)
    {
        close(pipes[1]);
        dup2(pipes[0], STDIN_FILENO);
        close(pipes[0]);
        runcmd(token->previous, env, prompt_info);
        exit(0);
    }
    close(pipes[0]);
    close(pipes[1]);
    wait(NULL);
}
