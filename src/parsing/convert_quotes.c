/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:32:42 by randrade          #+#    #+#             */
/*   Updated: 2025/01/14 14:22:04 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	quotes_nbr(char *str)
{
	size_t	quotes_nbr;

	quotes_nbr = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			str += quote_len(str) + 1;
			quotes_nbr++;
		}
		str++;
	}
	return (quotes_nbr);
}

static size_t	get_size_new_str(char *str)
{
	size_t	len;
	size_t	quotesnbr;

	len = ft_strlen(str);
	quotesnbr = quotes_nbr(str);
	return (len - (quotesnbr * 2));
}

static bool	ignore_quote(char str, char *quote)
{
	if ((str == '"' || str == '\'') && *quote == 0)
	{
		*quote = str;
		return (true);
	}
	if (str == *quote)
	{
		*quote = 0;
		return (true);
	}
	return (false);
}

static char	*convert(t_list *token)
{
	char	*new_str;
	char	quote;
	size_t	len;
	size_t	i;
	size_t	j;

	quote = 0;
	len = get_size_new_str(token->str);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	if (len != 0)
	{
		while (token->str[j])
		{
			if (ignore_quote(token->str[j], &quote) == true)
				j++;
			else
				new_str[i++] = token->str[j++];
		}
	}
	new_str[i] = '\0';
	return (free(token->str), new_str);
}

t_list	*convert_quotes(t_list *tokens_list)
{
	t_list	*token;

	token = tokens_list;
	while (token)
	{
		while (token->next && token->subtype != T_QUOTE)
			token = token->next;
		if (token)
		{
			token->str = convert(token);
			if (token->str == NULL)
				return (free_list(tokens_list), NULL);
		}
		token = token->next;
	}
	return (tokens_list);
}
