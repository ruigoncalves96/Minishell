/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/07 18:59:12 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static unsigned int	ft_token_len(char *prompt)
{
	size_t	i;
	char	token_type;
	char	quote;
	bool	active_quote;

	quote = 0;
	active_quote = false;
	i = 0;
	while (prompt[i])
	{
		token_type = ft_check_token_type(prompt[i]);
		ft_quote_mode_switch(&prompt[i], &active_quote, &quote);
		if (active_quote == false && token_type == OPERATOR)
			break ;
		i++;
	}
	if (i == 0)
	{
		if ((prompt[0] == '>' && prompt[1] == '>')
			|| (prompt[0] == '<' && prompt[1] == '<'))
			i = 2;
		else
			i = 1;
	}
	return (i);
}

static t_list	*ft_create_token(char **prompt)
{
	char	**token;
	size_t	token_len;
	int		token_type;

	token_len = ft_token_len(*prompt);
	token_type = ft_check_token_type(**prompt);
	token = ft_split_token(*prompt, token_len, token_type);
	if (token == NULL)
		return (NULL);
	*prompt += token_len;
	return (ft_lstnew(token));
}

t_list	*ft_build_tokens_list(char *prompt)
{
	t_list	*tokens;
	t_list	*node;

	tokens = NULL;
	while (*prompt)
	{
		ft_skip_spaces(&prompt);
		if (*prompt)
		{
			node = ft_create_token(&prompt);
			if (!node)
			{
				ft_free_list(tokens);
				return (NULL);
			}
			ft_lstadd_last(&tokens, node);
			ft_define_token_type(node);
		}
	}
	return (tokens);
}
