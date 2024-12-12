#include "../../includes/minishell.h"


/*
    arg[0] = Exit;
    arg[1] = ...; // O ideal e ser numero

    atol(arg[1]);

    //Evitar overflows caso passem o LONG_MAX OU LONG_MIN

    EXIT
    Retorna 0 sem receber nenhum parametro

    arg[1]
    Caso receba um numero ate 256 ele vai returna com o value do numero
    SE FOR MAIOR DO QUE UM BYTE TENHO DE FAZER O MOD

    exit se receber dois inputs numericos  nao vai sair
    exit 23 54534 ||
    exit
    bash: exit: too many arguments
-----------------------------------
    exit ao receber uma string vai dar mensagem de erro MAS SAI
///!RETURNA 2 PARA ERRO DE STRING
    redgtxt@DESKTOP-7SB9EC4:~/42/Minishell$ exit ola
    exit
    bash: exit: ola: numeric argument required
 */


/*
	eu acho que tenho os if state mal feitos
	corrigir isso
		dar handle caso passem certo tipos de argumentos
			tratar de strings
				tratar de mensagens de eroos
					e provavelmente estou me a esquecer de alguma coisa

*/

/*
    Funcao que vai tratar do exit
    Vai receber o builtins e o array de argumentos
    Vai retornar o exit status

    Vou receber tres argumentos no maximo 

    
 */

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
            return (0); // Retorna erro
        num = (num * 10) + (str[i] - '0');
        i++;
    }
    *result = num * neg;
    return (1); // Sucesso
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

//Create exit code
void create_exit_code(t_builtins *builtins, char *arr[])
{
    long num = 0;

    if (!arr[1]) 
    {
        builtins->exit_status = 0;
        return;
    }
    if (!check_digit(arr[1])) // Caso não seja um número válido
    {
        printf("bash: exit: %s: numeric argument required\n", arr[1]);
        builtins->exit_status = 2;
        return;
    }
    if (!ft_atol(arr[1], &num)) // Detecta overflow
    {
        printf("bash: exit: %s: numeric argument required\n", arr[1]);
        builtins->exit_status = 2;
        return;
    }
    if (num > 255 || num < 0) // Normaliza valores fora de 0-255
    {
        num = num % 256;
        if (num < 0)
            num += 256;
    }
    builtins->exit_status = num;
}

