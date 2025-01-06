/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:30:48 by randrade          #+#    #+#             */
/*   Updated: 2025/01/06 16:22:19 by randrade         ###   ########.fr       */
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
		ft_quote_mode_switch(s[i], &active_quote, &quote);
		if (active_quote == false)
		{
			if (ft_check_token(s[i]) != SPACE &&
				(ft_check_token(s[i + 1]) == SPACE || i + 1 == token_len))
				count++;
		}
		i++;
	}
	return (count);
}

static int	ft_wordlen(char *s)
{
	size_t	i;
	char	c;
	char	quote;
	bool	active_quote;

	quote = 0;
	active_quote = false;
	i = 0;
	while (s[i])
	{
		c = ft_check_token(s[i]);
		ft_quote_mode_switch(s[i], &active_quote, &quote);
		if (active_quote == false && (c == OPERATOR || c == SPACE))
			break ;
		i++;
	}
	return (i);
}

static char	*ft_alloc_word(char *ptr, char **s, size_t token_len, int token_type)
{
	size_t	word_len;

	if (token_type == WORD || token_type == QUOTE)
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
	size_t		count_words;
	size_t		i;

	if (token_type == WORD || token_type == QUOTE)
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
