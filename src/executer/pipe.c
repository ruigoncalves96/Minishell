#include "../../includes/minishell.h"

int  pipe_executer(t_token *token, t_env *env, t_prompt_info prompt_info)
{
    int pipes[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int status;

    if(pipe(pipes) == -1)
        return (perror("pipe"),-1);
    signal(SIGINT, SIG_IGN);
    left_pid = fork();
    if (left_pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        runcmd(token->previous, env, prompt_info);
        close_fds();
        cleanup_all(&prompt_info,token);
        exit(prompt_info.builtins->exit_code);
    }
    right_pid = fork();
    if (right_pid == 0)
    {
        dup2(pipes[0], STDIN_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        runcmd(token->next, env, prompt_info);
        close_fds();
        cleanup_all(&prompt_info,token);
        exit(prompt_info.builtins->exit_code);
    }
    close(pipes[0]);
    close(pipes[1]);
    waitpid(left_pid,&status,0);
    waitpid(right_pid,&status,0);
    set_signals();
    prompt_info.builtins->exit_code = get_exit_status(status);
    return (0);
}
