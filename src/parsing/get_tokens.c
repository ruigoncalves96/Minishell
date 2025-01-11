/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/11 01:54:04 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_token_len_def(t_list *token, char *str)
{
	size_t	i;
	size_t	quote_len;
	char	token_type;
	char	token_subtype;

	if (ft_strchr(OPERATOR_TOKENS, *str) != NULL)
	{
		token->subtype = ft_check_token_subtype(*str);
		token->type = OPERATOR;
		if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
			return (2);
		return (1);
	}
	quote_len = 0;
	i = 0;
	while (str[i])
	{
		token_type = ft_check_token_type(str[i]);
		token_subtype = ft_check_token_subtype(str[i]);
		if (token_subtype == T_QUOTE)
		{
			quote_len += ft_quote_len(&str[i]);
			if (quote_len == 0)
				return (ft_quote_error(), 0);
			i += quote_len;
			token->subtype = T_QUOTE;
		}
		if (token_type == OPERATOR || token_subtype == T_SPACE)
			break ;
		i++;
	}
	token->type = COMMAND;
	if (!token->subtype)
		token->subtype = T_WORD;
	return (i);
}

static t_list	*ft_create_token(char **prompt)
{
	t_list	*token;
	char	*str;
	size_t	len;

	token = ft_lstnew(NULL);
	if (!token)
		return (NULL);
	len = ft_token_len_def(token, *prompt);
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

t_list	*ft_build_tokens_list(char *prompt)
{
	t_list	*command;
	t_list	*token;

	command = NULL;
	while (*prompt)
	{
		ft_skip_spaces(&prompt);
		if (*prompt)
		{
			token = ft_create_token(&prompt);
			if (!token)
				return (ft_free_list(command), NULL);
			ft_lstadd_last(&command, token);
		}
	}
	return (command);
}
