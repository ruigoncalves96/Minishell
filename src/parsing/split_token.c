/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:30:48 by randrade          #+#    #+#             */
/*   Updated: 2025/01/08 15:47:20 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_words(char *s, size_t token_len)
{
	size_t	count;
	size_t	i;
	char	quote;
	bool	active_quote;

	quote = 0;
	active_quote = false;
	count = 0;
	i = 0;
	while (s[i] && i < token_len)
	{
		ft_quote_mode_switch(&s[i], &active_quote, &quote);
		if (active_quote == false)
		{
			if (ft_check_token_subtype(s[i]) != T_SPACE
				&& (ft_check_token_subtype(s[i + 1]) == T_SPACE
					|| i + 1 == token_len))
				count++;
		}
		i++;
	}
	if (count == 0)
		count = 1;
	return (count);
}

static int	ft_wordlen(char *s)
{
	size_t	i;
	char	token_subtype;
	char	quote;
	bool	active_quote;

	quote = 0;
	active_quote = false;
	i = 0;
	while (s[i])
	{
		token_subtype = ft_check_token_subtype(s[i]);
		ft_quote_mode_switch(&s[i], &active_quote, &quote);
		if (active_quote == false && (token_subtype == OPERATOR
				|| token_subtype == T_SPACE))
			break ;
		i++;
	}
	return (i);
}

static char	*ft_alloc_word(char *ptr, char **s, size_t token_len,
		int token_type)
{
	size_t	word_len;

	if (token_type == COMMAND)
		word_len = ft_wordlen(*s);
	else
		word_len = token_len;
	ptr = ft_calloc(word_len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, *s, word_len + 1);
	*s += word_len;
	return (ptr);
}

char	**ft_split_token(char *s, size_t token_len, int token_type)
{
	char	**ptr;
	size_t	count_words;
	size_t	i;

	if (token_type == COMMAND)
		count_words = ft_count_words(s, token_len);
	else
		count_words = 1;
	ptr = ft_calloc(count_words + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count_words)
	{
		ptr[i] = ft_alloc_word(ptr[i], &s, token_len, token_type);
		if (!ptr[i])
		{
			ft_free_double_array(ptr);
			return (NULL);
		}
		ft_skip_spaces(&s);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
