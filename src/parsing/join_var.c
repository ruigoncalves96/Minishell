/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:43:28 by randrade          #+#    #+#             */
/*   Updated: 2025/01/17 15:57:46 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_value_to_str(char *token_str, char *var_value,
		char *var_key_pos, size_t key_len)
{
	char	*new_token;
	size_t	value_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	value_len = ft_strlen(var_value);
	new_token = ft_calloc((ft_strlen(token_str) - key_len) + value_len,
			sizeof(char));
	if (!new_token)
		return (NULL);
	while (token_str[j])
	{
		if (&token_str[j] != var_key_pos)
			new_token[i++] = token_str[j++];
		else
		{
			i += ft_strlcpy(&new_token[i], var_value, value_len + 1);
			j += key_len + 1;
		}
	}
	new_token[i] = '\0';
	return (new_token);
}

char	*join_var(char *token_str, char *var_value, char *var_key_pos,
		size_t key_len)
{
	char	*new_token;
	bool	free_exit_code;

	free_exit_code = false;
	if (var_key_pos[1] == '?')
		free_exit_code = true;
	new_token = add_value_to_str(token_str, var_value, var_key_pos, key_len);
	if (free_exit_code == true)
		free(var_value);
	free(token_str);
	return (new_token);
}
