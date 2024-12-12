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
int array_size(char **array)
{
    int count;

    if (!array) 
        return 0;

    count = 0;
    while (array[count] != NULL) 
        count++;
    return count;
}