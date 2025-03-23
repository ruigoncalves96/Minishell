#include "../../includes/minishell.h"


static int ft_skip_whitespace(const char *str, int *i, int *neg)
{
    while (str[*i] && (str[*i] < 32))
        (*i)++;
    if (str[*i] == '+' || str[*i] == '-')
    {
        if (str[*i] == '-')
            *neg = -1;
        (*i)++;
    }
    return (1);
}

static int ft_check_overflow(long num, char digit, int neg)
{
    long max_last_digit;
    
    if (neg == 1)
        max_last_digit = LONG_MAX % 10;
    else
        max_last_digit = -(LONG_MIN % 10);
    
    if (num > LONG_MAX / 10)
        return (0);
    if (num == LONG_MAX / 10 && (digit - '0') > max_last_digit)
        return (0);
    return (1);
}

int ft_atol(const char *str, long *result)
{
    long num;
    int neg;
    int i;

    num = 0;
    neg = 1;
    i = 0;
    *result = 0;
    
    ft_skip_whitespace(str, &i, &neg);
    
    while (str[i] >= '0' && str[i] <= '9')
    {
        if (!ft_check_overflow(num, str[i], neg))
            return (0);
        num = (num * 10) + (str[i] - '0');
        i++;
    }
    *result = num * neg;
    return (1);
}