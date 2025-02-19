#include "../../includes/minishell.h"

static int  ft_atol(const char *str, long *result)
{
    long    num;
    int     neg;
    int     i;

    num = 0;
    neg = 1;
    i = 0;
    *result = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'
            || str[i] == '\n' || str[i] == '\r'
            || str[i] == '\v' || str[i] == '\f'))
        i++;
    if (str[i] == '+' || str[i] == '-') // Lida com sinal
    {
        if (str[i] == '-')
            neg = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        if (num > (LONG_MAX - (str[i] - '0')) / 10) // Detecta overflow
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
void cleanup_all(t_prompt_info *prompt_info, t_token *tokens)
{
    rl_clear_history();

    if (prompt_info->prompt)
    {
        free(prompt_info->prompt);
        prompt_info->prompt = NULL;
    }

    if (tokens)
        ft_free_token_list(tokens);
    
    if (prompt_info->env)
    {
        free_env(prompt_info->env);
         prompt_info->env = NULL;
    }
}

//Create exit code
void exit_manager(char **args, t_builtins *builtins,t_prompt_info *prompt_info,t_token *tokens)
{
    long num = 0;

    printf("exit\n");

    if (array_size(args) == 1) {
        builtins->exit_code = 0;
        printf("Codigo de saida: %d\n", builtins->exit_code);///////DEBUG
        cleanup_all(prompt_info, tokens);
        exit(0);
    }

    if (!check_digit(args[1]))  // Se não for número
    {
        ft_putstr_fd("bash: exit: ",2);
        ft_putstr_fd(args[1],2);
        ft_putstr_fd(": numeric argument required\n",2);
        builtins->exit_code = 2;
        cleanup_all(prompt_info, tokens);
        exit(2);
    }

    if (array_size(args) > 2)  // Muitos argumentos
    {
        ft_putstr_fd("bash: exit: too many arguments\n",2);
        return;  // Não sai se houver múltiplos argumentos
    }

    if (!ft_atol(args[1], &num))  // Verifica overflow
    {
        ft_putstr_fd("bash: exit: ",2);
        ft_putstr_fd(args[1],2);
        ft_putstr_fd(":  numeric argument required\n",2);
        cleanup_all(prompt_info, tokens);
        builtins->exit_code = 2;
        cleanup_all(prompt_info, tokens);
        exit(2);
    }

    // Normaliza o número para 0-255
    num = num % 256;
    if (num < 0)
        num += 256;
    builtins->exit_code = (int)num;
    printf("Codigo de saida: %d\n", builtins->exit_code);///////DEBUG
    cleanup_all(prompt_info, tokens);
    exit((int)num);
}

