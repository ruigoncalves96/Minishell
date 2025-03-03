#include "../../includes/minishell.h"

static int  ft_atol(const char *str, long *result)
{
    long    num;
    int     neg;
    int     i;
    long    max_last_digit;

    num = 0;
    neg = 1;
    i = 0;
    *result = 0;
    while (str[i] && (str[i] < 32))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            neg = -1;
        i++;
    }
    if (neg == 1)
        max_last_digit = LONG_MAX % 10;
    else
        max_last_digit = -(LONG_MIN % 10);

    while (str[i] >= '0' && str[i] <= '9')
    {
        if (num > LONG_MAX / 10)
            return (0);
        if (num == LONG_MAX / 10 && (str[i] - '0') > max_last_digit)
            return (0);
        num = (num * 10) + (str[i] - '0');
        i++;
    }
    *result = num * neg;
    return (1);
}

static int check_digit(const char *str)
{
    int i = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}
void close_fds()
{
    int fd = 3;
    while (fd < 256)
    {
        close(fd);
        fd++;
    }
}

void cleanup_all(t_prompt_info *prompt_info, t_token *tokens)
{
    rl_clear_history();

    if (prompt_info->prompt)
    {
        free(prompt_info->prompt);
        prompt_info->prompt = NULL;
    }

    if (tokens)
        free_token_tree(go_to_tree_top(tokens));

    if (prompt_info->env)
    {
         free_env(prompt_info->env);
         prompt_info->env = NULL;
    }

    close_fds();
}
static void free_error_exit(char **args, t_builtins *builtins,t_prompt_info *prompt_info,t_token *tokens)
{
    print_error("exit",args[1],EXIT_NUMERIC_ERROR,true);
    builtins->exit_code = 2;
    cleanup_all(prompt_info, tokens);
    exit(2);
}
void exit_manager(char **args, t_builtins *builtins,t_prompt_info *prompt_info,t_token *tokens)
{
    long num;

    num = 0;
    printf("exit\n");
    if (array_size(args) == 1) {
        builtins->exit_code = 0;
        cleanup_all(prompt_info, tokens);
        exit(0);
    }
    if (!check_digit(args[1]))
        free_error_exit(args,builtins,prompt_info,tokens);
    if (array_size(args) > 2)
    {
        print_error("exit",NULL,TOO_MANY_ARGS,true);
        builtins->exit_code = 1;
        return;
    }
    if (!ft_atol(args[1], &num))
        free_error_exit(args,builtins,prompt_info,tokens);

    num %= 256;
    if (num < 0)
        num += 256;
    builtins->exit_code = (int)num;
    cleanup_all(prompt_info, tokens);
    exit((int)num);
}
