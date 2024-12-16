#include "../../includes/minishell.h"

// Extrai nome da variável de uma string no formato VAR=VALUE
char *get_key(char *env)
{
    int len = 0;
    while (env[len] && env[len] != '=')
        len++;
    char *key = malloc(len + 1);
    if (!key)
        return NULL;
    ft_strlcpy(key, env, len + 1);
    return key;
}

// Ordena as variáveis de ambiente em ordem alfabetica (ASCII)
void sort_env_ascii_order(char **env)
{
    int i, j;
    char *tmp;

    i = 0;
    while (env[i])
    {
        j = i + 1;
        while (env[j])
        {
            char *key1 = get_key(env[i]);
            char *key2 = get_key(env[j]);
            if (strcmp(key1, key2) > 0) // Compara as chaves
            {
                tmp = env[i];
                env[i] = env[j];
                env[j] = tmp;
            }
            free(key1);
            free(key2);
            j++;
        }
        i++;
    }
}

// Imprime as variáveis de ambiente no formato declare -x 
void print_x_declaration(char **env)
{
    int i = 0;
    while (env[i])
    {
        printf("declare -x ");
        char *key = get_key(env[i]);
        printf("%s", key);

        // Verifica se há um valor associado (presença de '=')
        char *value = ft_strchr(env[i], '=');
        if (value)
            printf("=\"%s\"", value + 1);

        printf("\n");
        free(key);
        i++;
    }
}
void handle_export(char **export_env)
{
    sort_env_ascii_order(export_env);
    print_x_declaration(export_env);
}