/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:43:28 by randrade          #+#    #+#             */
/*   Updated: 2025/01/11 18:18:35 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_find_var(char **str)
{
	size_t	quote_len;
	bool	double_quote;

	quote_len = 0;
	double_quote = false;
	while (**str)
	{
		if (**str == '"')
			double_quote ^= 1;
		else if (double_quote == false && **str == '\'')
		{
			quote_len += ft_quote_len(*str);
			*str += quote_len;
		}
		if (**str == '$')
			return (*str);
		(*str)++;
	}
	return (*str);
}

//	VARS CAN ONLY HAVE LETTERS NUMBERS AND UNDERSCORE
//	AND THE FIRST CHAR HAS TO BE A LETTER
size_t	ft_var_key_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_get_var_key(char **prompt)
{
	char	*key;
	size_t	key_len;

	(*prompt)++;
	key_len = ft_var_key_len(*prompt);
	if (key_len == 0)
		return (NULL);
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, *prompt, key_len + 1);
	(*prompt) += key_len;
	return (key);
}

static char	*ft_get_var_value(t_env *env, char *key)
{
	t_env_var	*var;
	char	*var_value;

	var_value = NULL;
	var = env->vars;
	while (var)
	{
		if (ft_strncmp(var->key, key, ft_strlen(key)) != 0)
		{
			var_value = var->value;
			break ;
		}
		var = var->next;
	}
	i = 0;
	while (var_value[i])
	{
		if (ft_check_token_type(var_value[i]) == OPERATOR)
			ft_comment_operator(var_value, i);
	}
	return (NULL);
}

static char	*ft_expand(char *prompt, char *dollar, char *var_key, char *var_value)
{

}

void	ft_expand_vars(t_prompt_info *prompt_info)
{
	char	*prompt;
	char	*var_key;
	char	*var_value;

	var_key = NULL;
	var_value = NULL;
	prompt = prompt_info->prompt;
	while (ft_find_var(&prompt) != NULL)
	{
		var_key = ft_get_var_key(&prompt);
		if (var_key == NULL)
			return ;
		var_value = ft_get_var_value(prompt_info->env, var_key);
		if (var_value == NULL)
			return ;
		prompt_info->prompt = ft_expand(prompt_info->prompt, prompt, var_key, var_value);
		if (prompt == NULL)
			return ;
		free(var_key);	
		free(var_value);	
	}
	free(prompt);
}


//	FIND DOLLAR
//		GET VAR_KEY
//		SEND VAR_KEY TO FIND VAR_VALUE
//			IF NULL
//				RETURN SPACE OR NULL
//			ELSE
//				RETURN VALUE
//		EXPAND VAR_VALUE IN PROMPT
//
//
//
		//	FIND VARIABLE WITH VAR_KEY AND RETURN VAR_VALUE
		//	CHECK IF VAR HAS OPERATORS INSIDE
		//	IF TRUE
		//		PUT IN BETWEEN ''
		//		RETURN NEW STR WITH OPERATOR
