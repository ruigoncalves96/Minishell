/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/06 16:22:10 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static unsigned int	ft_token_len(char *prompt)
{
	size_t	i;
	char	token;
	char	quote;
	bool	active_quote;

	quote = 0;
	active_quote = false;
	i = 0;
	while (prompt[i])
	{
		token = ft_check_token(prompt[i]);
		ft_quote_mode_switch(prompt[i], &active_quote, &quote);
		if (active_quote == false && token == OPERATOR)
			break ;
		i++;
	}
	if (i == 0)
	{
		if ((prompt[0] == '>' && prompt[1] == '>') ||
			(prompt[0] == '<' && prompt[1] == '<'))
			i = 2;
		else
			i = 1;
	}
	return (i);
}

//	CREATE TOKEN TYPE **ARRAY
static t_list	*ft_create_token(char **prompt)
{
	char	**token;
	size_t	token_len;
	int	token_type;

	token_len = ft_token_len(*prompt);
	token_type = ft_check_token(**prompt);
	token = ft_split_token(*prompt, token_len, token_type);
	if (token == NULL)
		return (NULL);
	*prompt += token_len;
	return (ft_lstnew(token, token_type));
}

//	BUILD LINKED LIST
t_list	*ft_get_tokens(char *prompt)
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
			ft_define_token(node);
		}
	}
	return (tokens);
}
