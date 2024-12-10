#include "../../includes/minishell.h"


void free_double_array(char *array[])
{
    int i;

    if (array == NULL)
        return;

    i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }

    free(array);
}

void	ft_print_double_array(char **array)
{
	int	i;

	if (!array) 
		return ;
	i = 0;
	while (array[i]) 
	{
		printf("%s\n", array[i]); 
		i++;
    }
}
