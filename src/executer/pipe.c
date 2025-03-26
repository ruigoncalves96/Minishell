#include "../../includes/minishell.h"

static void execute_pipe(t_token *token, t_prompt_info *prompt_info, int pipes[2], int std_fileno)
{
    if (std_fileno == STDOUT_FILENO)
        dup2(pipes[1], STDOUT_FILENO);
    else if (std_fileno == STDIN_FILENO)
        dup2(pipes[0], STDIN_FILENO);
    close_pipes(pipes);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    runcmd(token, *prompt_info);
    close_fds();
    cleanup_all(prompt_info,token);
    exit(prompt_info->builtins->exit_code);
}

int  pipe_executer(t_token *token, t_prompt_info prompt_info)
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
        execute_pipe(token->previous, &prompt_info, pipes, STDOUT_FILENO);
    right_pid = fork();
    if (right_pid == 0)
        execute_pipe(token->next, &prompt_info, pipes, STDIN_FILENO);
    close_pipes(pipes);
    waitpid(left_pid,&status,0);
    waitpid(right_pid,&status,0);
    set_signals();
    prompt_info.builtins->exit_code = get_exit_status(status);
    return (0);
}
