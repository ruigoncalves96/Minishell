#include "../../includes/minishell.h"

void	print_double_array(char **array)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
