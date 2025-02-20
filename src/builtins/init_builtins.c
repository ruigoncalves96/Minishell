#include "../../includes/minishell.h"

void init_variables_builtins(t_builtins *builtins)
{
    builtins->echo_flag = true;
}
int is_builtin(char *cmd)
{
    const char *builtins[] = {"pwd", "echo", "env", "cd", "export", "unset", "exit", NULL};
    int i;

    i = 0;
    while (builtins[i])
    {
        if (ft_strcmp(cmd, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}
/*
static int env_manager(char **str,t_env *env)
{
    if (str == NULL || *str == NULL)
        return 1;
    if(array_size(str) == 1)
    {
        print_env_list(env);
        return 0;
    }

    if(array_size(str) == 2 && ft_strcmp(str[1]," -i"))
        return 0;
    else
           ft_putstr_fd("Too many arguments in env\n",2);

    return 1;
}
*/

int execute_builtin(t_token *tokens, t_prompt_info prompt_info,t_builtins *builtins)
{
    if (!tokens || !tokens->token || !*tokens->token)
        return (0);

    if (!is_builtin(*tokens->token))
        return (0);

    if (ft_strcmp(*tokens->token, "env") == 0)
        print_env_list(prompt_info.env);
    else if (ft_strcmp(*tokens->token, "pwd") == 0)
        pwd_builtin();
    else if (ft_strcmp(*tokens->token, "cd") == 0)
        cd_manager(tokens->token, prompt_info.env);
    else if (ft_strcmp(*tokens->token, "export") == 0)
        export_manager(tokens->token, prompt_info.env);
    else if (ft_strcmp(*tokens->token, "unset") == 0)
        manager_unset(tokens->token, prompt_info.env);
    else if (ft_strcmp(*tokens->token, "echo") == 0)
        handle_echo(tokens->token);
	else if (ft_strcmp(*tokens->token, "exit") == 0)
		exit_manager(tokens->token,builtins,&prompt_info,tokens);
    return (1);
}

// Aloca e constrói uma string no formato "KEY=VALUE"
static char *create_env_string(const char *key, const char *value)
{
    size_t key_len = ft_strlen(key);
    size_t value_len = ft_strlen(value);
    char *env_str = ft_calloc(key_len + value_len + 2, 1);
    if (!env_str)
        return (NULL);
    ft_strlcpy(env_str, key,key_len + 1);
    ft_strlcat(env_str, "=",key_len + 2);
    ft_strlcat(env_str, value,key_len + value_len + 2);
    return (env_str);
}

/// @brief Converte uma linked list de ambiente (t_env) para um array de strings no formato "KEY=VALUE".
/// @param env Estrutura de ambiente.
/// @return Um array de strings ou NULL em caso de falha.
char **convert_env_to_array(t_env *env)
{
    char **envp;
    t_env_var *current;
    int i;

    if (!env || env->var_count <= 0)
        return (NULL);

    envp = malloc((env->var_count + 1) * sizeof(char *));
    if (!envp)
        return (NULL);

    current = env->vars;
    i = 0;
    while (current)
    {
        if (current->is_export_only == 0)
        {
            envp[i] = create_env_string(current->key, current->value);
            if (!envp[i])
            {
                ft_free_double_array(envp);
                return (NULL);
            }
            i++;
        }
        current = current->next;
    }
    envp[i] = NULL;
    return (envp);
}
