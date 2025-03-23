#include "../../includes/minishell.h"

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

static int handle_specific_builtin(char **args, t_prompt_info *prompt_info, t_builtins *builtins,t_token *tokens)
{
    if (ft_strcmp(*args, "env") == 0)
        print_env_list(prompt_info->env);
    else if (ft_strcmp(*args, "pwd") == 0)
        pwd_builtin();
    else if (ft_strcmp(*args, "cd") == 0)
    {
        if(cd_manager(args, prompt_info->env) == -1)
            builtins->exit_code = 1;
    }
    else if (ft_strcmp(*args, "export") == 0)
        export_manager(args, prompt_info->env, builtins);
    else if (ft_strcmp(*args, "unset") == 0)
        manager_unset(args, prompt_info->env);
    else if (ft_strcmp(*args, "echo") == 0)
        handle_echo(args);
    else if (ft_strcmp(*args, "exit") == 0)
        exit_manager(args, builtins, prompt_info, tokens);
    return (1);
}

int execute_builtin(t_token *tokens, t_prompt_info prompt_info, t_builtins *builtins)
{
    if (!tokens || !tokens->token || !*tokens->token || !is_builtin(*tokens->token))
        return (0);

    builtins->exit_code = 0;
    return (handle_specific_builtin(tokens->token, &prompt_info, builtins, tokens));
}

// Create a string in format "KEY=VALUE"
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
//Convert list in an array
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
                return(ft_free_double_array(envp),NULL);
            i++;
        }
        current = current->next;
    }
    envp[i] = NULL;
    return (envp);
}

