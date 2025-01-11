/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:43:28 by randrade          #+#    #+#             */
/*   Updated: 2025/01/10 18:31:40 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_find_var(char *str)
{
	int	quote_len;
	bool	double_quote;

	quote_len = 0;
	double_quote = false;
	while (*str)
	{
		if (*str == '"')
			double_quote ^= 1;
		else if (double_quote == false && *str == '\'')
		{
			quote_len += ft_quote_len(str);
			str += quote_len;
		}
		if (*str == '$')
			return (str);
		str++;
	}
	return (str);
}

int	ft_var_key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || (i != 0 && ft_isdigit(str[i]))
				|| (i != 0 && str[i] == '_'))
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_get_var_key(char **prompt)
{
	char	*key;
	int	key_len;

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

void	ft_expand_vars(t_prompt_info *prompt_info)
{
	char	*prompt;
	char	*var_key;

	prompt = prompt_info->prompt;
	while (*prompt)
	{
		prompt = ft_find_var(prompt);
		if (prompt == NULL)
			return ;
		var_key = ft_get_var_key(&prompt);
		if (var_key == NULL)
			return ;
//		FIND VARIABLE WITH VAR_KEY AND GET VAL_VALUE
	}
}


//	FIND DOLLAR
//		GET VAR_KEY
//		SEND VAR_KEY TO FIND VAR_VALUE
//			IF NULL
//				RETURN SPACE OR NULL
//			ELSE
//				RETURN VALUE
//		EXPAND VAR_VALUE IN PROMPT
