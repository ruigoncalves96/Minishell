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

char *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
    char *result;
    size_t len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;

    result = ft_calloc(len,1);
    if (!result)
        return NULL;

    ft_strlcpy(result, s1, len);
    ft_strlcat(result, s2, len);
    ft_strlcat(result, s3, len);

    return result;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
