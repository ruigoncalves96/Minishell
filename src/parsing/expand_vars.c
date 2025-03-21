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
#include <stdbool.h>
#include <unistd.h>

static t_list	*build_list(t_list **new_list, t_list *token)
{
	t_list	*new_token;
	char	*token_str;
	char	*new_str;
	size_t	wordlen;

	token_str = token->str;
	while (*token_str)
	{
		wordlen = strlen_until_spaces(token_str);
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
		skip_spaces(&token_str);
	}
	return (*new_list);
}

static t_list	*split_and_link(t_list **tokens_list, t_list **token)
{
	t_list	*new_list;

	new_list = NULL;
	if (ft_strlen((*token)->str) != strlen_until_spaces((*token)->str))
	{
		build_list(&new_list, *token);
		if (!new_list)
			return (NULL);
		insert_list(tokens_list, *token, new_list);
		*token = new_list;
	}
	return (*tokens_list);
}

char	*join_var(char *token_str, char *var_value, char *var_key_pos, size_t key_len)
{
	char	*new_token;
	bool    free_exit_code;
	size_t	value_len;
	size_t	i;
	size_t	j;

	if (var_key_pos[1] == '?')
	    free_exit_code = true;
	else
	    free_exit_code = false;
	value_len = ft_strlen(var_value);
	new_token = ft_calloc((ft_strlen(token_str) - key_len) + value_len, sizeof(char));
	if (!new_token)
		return (NULL);
	i = 0;
	j = 0;
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
	if (free_exit_code == true)
	    free(var_value);
	free(token_str);
	return (new_token);
}

static char	*expand(t_prompt_info prompt_info, t_list **tokens_list, t_list **token)
{
	char   *var_value;
	char   *dollar;
	bool   double_quotes;
	size_t var_value_len;

	var_value = NULL;
	double_quotes = false;
	var_value_len = 0;
	while (1)
	{
        dollar = (*token)->str;
        dollar += var_value_len;
	    dollar = find_expand_dollar(dollar, &double_quotes);
		if (!dollar)
			break ;
		var_value = find_var_value(prompt_info, dollar);
		if (double_quotes == true)
		    var_value_len = ft_strlen(var_value) + strlen_until_expansion((*token)->str, dollar);
		else
		    var_value_len = strlen_until_spaces(var_value) + strlen_until_expansion((*token)->str, dollar);
		(*token)->str = join_var((*token)->str, var_value, dollar, var_key_len(dollar + 1));
		if (!(*token)->str)
			return (NULL);
		if (double_quotes == false)
			split_and_link(tokens_list, token);
	}
	return ((*token)->str);
}

t_list	*expand_vars(t_prompt_info prompt_info, t_list **tokens_list)
{
	t_list	*token;
	bool	double_quotes;

	double_quotes = false;
	token = *tokens_list;
	while (token)
	{
		if ((token->previous && check_redirect_type(token->previous->str) != HEREDOC) && find_expand_dollar(token->str, &double_quotes))
		{
			if (expand(prompt_info, tokens_list, &token) == NULL)
			     return (NULL);
			if (double_quotes == true)
			     double_quotes ^= 1;
		}
;		token = token->next;
	}
	return (*tokens_list);
}
