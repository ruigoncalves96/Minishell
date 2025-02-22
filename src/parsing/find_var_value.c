/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:17:06 by randrade          #+#    #+#             */
/*   Updated: 2025/01/17 14:55:01 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

size_t	var_key_len(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] &&  (ft_isdigit(str[i]) || str[i] == '?'))
		return (1);
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_' || str[i] == '?')
			i++;
		else
			break ;
	}
	return (i);
}

static char	*get_var_key(char *dollar)
{
	char	*key;
	size_t	key_len;

	dollar++;
	key_len = var_key_len(dollar);
	if (key_len == 0)
		return (NULL);
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, dollar, key_len + 1);
	dollar+= key_len;
	return (key);
}

static char	*get_var_value(t_env_var *env, char *key)
{
	t_env_var	*var;
	char	*var_value;

	var_value = NULL;
	var = env;
	while (var)
	{
		if (ft_strncmp(var->key, key, ft_strlen(var->key)) == 0)
		{
			var_value = var->value;
			break ;
		}
		var = var->next;
	}
	return (var_value);
}

char	*find_var_value(t_prompt_info *prompt_info, char *dollar)
{
	char	*var_key;
	char	*var_value;

	if (dollar[1] == '?')
	    return (ft_itoa(prompt_info->builtins->exit_code));
	var_key = get_var_key(dollar);
	if (!var_key)
		return (NULL);
	var_value = get_var_value(prompt_info->env->vars, var_key);
	free(var_key);
	if (!var_value)
		return (NULL);
	return (var_value);
}
