#include "../../includes/minishell.h"

static t_env_var *copy_env_list(t_env_var *list)
{
    t_env_var *copy = NULL;
    t_env_var *current = list;

    while (current)
    {
        t_env_var *new_node = ft_calloc(1, sizeof(t_env_var));
        if (!new_node)
            return NULL;

        new_node->key = ft_strdup(current->key);
        new_node->is_export_only = current->is_export_only;
        if (current->value)
            new_node->value = ft_strdup(current->value);
        else
            new_node->value = NULL;

        if (!copy)
        {
            copy = new_node;
        }
        else
        {
            t_env_var *temp = copy;
            while (temp->next)
                temp = temp->next;
            temp->next = new_node;
            new_node->prev = temp;
        }

        current = current->next;
    }
    return copy;
}
static void print_x_declaration_list(t_env_var *vars)
{
    t_env_var *current = vars;
    while (current)
    {
        if (current->is_export_only)
        {
            // Variáveis que são export-only
            printf("declare -x %s", current->key);
            if (current->value)
                printf("=\"%s\"", current->value);
            printf("\n");
        }
        else
        {
            // Variáveis normais
            printf("declare -x %s", current->key);
            if (current->value)
                printf("=\"%s\"", current->value);
            printf("\n");
        }
        current = current->next;
    }
}

static void sort_env_list(t_env_var *head)
{
    if (!head)
        return;

    t_env_var *current;
    t_env_var *next_node;
    int sorted;
    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        current = head;

        while (current->next)
        {
            next_node = current->next;
            if (ft_strcmp(current->key, next_node->key) > 0)
            {
                char *temp_key = current->key;
                char *temp_value = current->value;
                int temp_flag = current->is_export_only;

                current->key = next_node->key;
                current->value = next_node->value;
                current->is_export_only = next_node->is_export_only;

                next_node->key = temp_key;
                next_node->value = temp_value;
                next_node->is_export_only = temp_flag;

                sorted = 0;
            }
            current = current->next;
        }
    }
}



static void free_env_copy(t_env_var *list)
{
    t_env_var *current;
    while (list)
    {
        current = list;
        list = list->next;
        free(current->key);
        free(current->value);
        free(current);
    }
}

void handle_export(t_env *env)
{
    t_env_var *env_copy = copy_env_list(env->vars);
    if (!env_copy)
        return;

    sort_env_list(env_copy);
    print_x_declaration_list(env_copy);
    free_env_copy(env_copy);
}