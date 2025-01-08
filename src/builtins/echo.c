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
   if(echo_flag == true)
    printf("\n");
}

void handle_echo(int argc, char *argv[])
{
    t_builtins vars;
    int start = 2;

    // Inicializa as variáveis do comando
    vars.echo_flag = true;

    if (argc > 2 && strcmp(argv[2], "-n") == 0)
    {
        vars.echo_flag = false;
        start = 3; // Ignora o argumento "-n"
    }

    echo(&argv[start], vars.echo_flag);
}
