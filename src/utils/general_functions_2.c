#include "../../includes/minishell.h"

size_t lst_size(t_list *list)
{
    size_t i;

    i = 0;
    while (list)
    {
        i++;
        list = list->next;
    }
    return i;
}

size_t  array_len(char **array)
{
    size_t  i;

    i = 0;
    if (!array)
        return (0);
    while (array[i])
        i++;
    return (i);
}
