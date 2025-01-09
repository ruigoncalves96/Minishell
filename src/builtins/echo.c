#include "../../includes/minishell.h"
#include <string.h>

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

void handle_echo(char *argv[])
{
    t_builtins vars;
    int start = 1;

    // Inicializa as variáveis do comando
    vars.echo_flag = false;

    if(argv[1])
    {
        while (ft_strcmp(argv[start], "-n") == 0)
        {
            vars.echo_flag = true;
            start++; // Ignora o argumento "-n"
            if (!argv[start])
                break;
        }
    }


    echo(&argv[start], vars.echo_flag);
}
