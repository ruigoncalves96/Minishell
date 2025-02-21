#include "../../includes/minishell.h"

static void echo(char **arr, bool echo_flag)
{
   int i;

   i = 0;
   while (arr[i])
   {
     printf("%s", arr[i]);
        if (arr[i + 1])
            printf(" ");
        i++;
   }
   if(echo_flag == false)
    printf("\n");
}

static bool is_valid_n_flag(const char *str)
{
    int i;

    if (!str || str[0] != '-')
        return false;

    i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return false;
        i++;
    }
    //Vou checar se existe um mais que um n depois do traço
    return (i > 1);
}
void handle_echo(char *argv[])
{
    t_builtins vars;
    int start = 1;

    // Inicializa as variáveis do comando
    vars.echo_flag = false;

    if(argv[1])
    {
        while (argv[start] && is_valid_n_flag(argv[start]))
        {
            vars.echo_flag = true;
            start++; // Ignora o argumento "-n"
            if (!argv[start])
                break;
        }
    }
    echo(&argv[start], vars.echo_flag);
}
