/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/11 18:01:13 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	operator_len_def(t_list *token, char *str)
{
	token->subtype = check_token_subtype(*str);
	token->type = OPERATOR;
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
		return (2);
	return (1);
}

static size_t	command_len_def(t_list *token, char *str)
{
	size_t	i;
	size_t	quotelen;
	char	token_type;
	char	token_subtype;

	quotelen = 0;
	i = 0;
	while (str[i])
	{
		token_type = check_token_type(str[i]);
		token_subtype = check_token_subtype(str[i]);
		if (token_subtype == T_QUOTE)
		{
			quotelen = quote_len(&str[i]);
			if (quotelen == 0)
				return (0);
			i += quotelen;
			token->subtype = T_QUOTE;
		}
		if (token_type == OPERATOR || token_subtype == T_SPACE)
			break ;
		i++;
	}
	return (i);
}

static size_t	token_len_def(t_list *token, char *str)
{
	size_t	len;

	len = 0;
	if (check_token_type(*str) == OPERATOR)
		len = operator_len_def(token, str);
	else
	{
		len = command_len_def(token, str);
		if (len == 0)
			return (quote_error(), 0);
		token->type = COMMAND;
		if (!token->subtype)
			token->subtype = T_WORD;
	}
	return (len);
}

static t_list	*create_token(char **prompt)
{
	t_list	*token;
	char	*str;
	size_t	len;

	token = ft_lstnew(NULL);
	if (!token)
		return (NULL);
	len = token_len_def(token, *prompt);
	if (len == 0)
		return (free(token), NULL);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (free(token), NULL);
	ft_strlcpy(str, *prompt, len + 1);
	token->str = str;
	*prompt += len;
	return (token);
}

t_list	*build_tokens_list(char *prompt)
{
	t_list	*tokens_list;
	t_list	*token;

	tokens_list = NULL;
	while (*prompt)
	{
		skip_spaces(&prompt);
		if (*prompt)
		{
			token = create_token(&prompt);
			if (!token)
				return (free_list(tokens_list), NULL);
			ft_lstadd_last(&tokens_list, token);
		}
	}
	return (tokens_list);
}
