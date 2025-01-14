/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:43:28 by randrade          #+#    #+#             */
/*   Updated: 2025/01/14 17:37:42 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_join_var(char *token_str, char *var_value, char *var_key, size_t key_len)
{
	char	*new_token;
	size_t	value_len;
	size_t	i;
	size_t	j;

	value_len = ft_strlen(var_value);
	new_token = ft_calloc((ft_strlen(token_str) - key_len) + value_len, sizeof(char));
	if (!new_token)
		return (NULL);
	i = 0;
	j = 0;
	while (token_str[j])
	{
		if (&token_str[j] != var_key)
			new_token[i++] = token_str[j++]; 
		else
		{
			i += ft_strlcpy(&new_token[i], var_value, value_len + 1);
			j += key_len + 1;
		}
	}
	new_token[i] = '\0';
	free(token_str);
	return (new_token);
}

static char	*ft_expand(t_env_var *env, t_list *token)
{
	char	*var_value;
	char	*dollar;

	while (1)
	{
		dollar = ft_find_var(token->str);
		if (!dollar)
			break ; 
		var_value = ft_find_var_value(env, dollar);
		token->str = ft_join_var(token->str, var_value, dollar, ft_var_key_len(dollar + 1));
		if (!token->str)
			return (NULL);
	}
	return (token->str);
}

static t_list	*ft_build_list(t_list **new_list, t_list *token)
{
	t_list	*new_token;
	char	*token_str;
	char	*new_str;
	size_t	wordlen;

	token_str = token->str;
	while (*token_str)
	{
		wordlen = ft_strlen_until_spaces(token_str);
		new_str = ft_calloc(wordlen + 1, sizeof(char));
		if (!new_str)
			return (NULL);
		ft_strlcpy(new_str, token_str, wordlen + 1);
		new_token = ft_lstnew(new_str);
		if (!new_token)
			return (free(new_str), NULL);
		ft_lstadd_last(new_list, new_token);
		new_token->type = COMMAND;
		new_token->subtype = T_WORD;
		token_str += wordlen;
		ft_skip_spaces(&token_str);
	}
	return (*new_list);
}


static t_list	*ft_split_and_link(t_list **tokens_list, t_list **token)
{
	t_list	*new_list;

	new_list = NULL;
	if (ft_strlen((*token)->str) != ft_strlen_until_spaces((*token)->str))
	{
		ft_build_list(&new_list, *token);
		if (!new_list)
			return (NULL);
		ft_insert_list(tokens_list, *token, new_list);
		*token = new_list;
	}
	return (*tokens_list);
}

t_list	*ft_expand_vars(t_prompt_info *prompt_info, t_list **tokens_list)
{
	t_list	*token;

	token = *tokens_list;
	while (token)
	{
		if (ft_find_var(token->str))
		{
			ft_expand(prompt_info->env->vars, token);
			if (ft_split_and_link(tokens_list, &token) == NULL)
				return (ft_free_list(*tokens_list), NULL);
		}
		token = token->next;
	}
	return (*tokens_list);
}
