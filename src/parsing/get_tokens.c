/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/04 17:15:19 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	ft_check_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (OPERATOR);
	else if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v')
		return (SPACE);
	else if (c == '"' || c == 39)
		return (QUOTE);
	else
		return (WORD);
}

static unsigned int	ft_check_quotes(char **prompt, unsigned int *index, char quote)
{
	unsigned int	i;

	i = 1;
	while (prompt[0][i] && prompt[0][i] != quote)
		i++;
	if (prompt[0][i] == '\0')
		return (0);
	*prompt += i;
	*index += i;
	return (i);
}

static unsigned int	ft_token_len(char *prompt)
{
	char	c;
	unsigned int	i;

	i = 0;
	while (*prompt)
	{
		c = ft_check_token(*prompt);
		if (c == QUOTE)
			ft_check_quotes(&prompt, &i, *prompt);
		else if ((c == OPERATOR | c == SPACE))
			break ;
		i++;
		prompt++;
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

static void	ft_create_token(char **prompt, t_list **tokens)
{
	t_list	*node;
	char	*token;
	unsigned int	token_len;

	token_len = ft_token_len(*prompt);
	token = ft_calloc(token_len + 1, sizeof(char));
	if (!token)
		return ;
	ft_strlcpy(token, *prompt, token_len + 1);
	node = ft_lstnew(token);
	ft_lstadd_last(tokens, node);
	*prompt += token_len;
	if (ft_check_token(node->str[0]) == OPERATOR)
		node->operator = true;
}

t_list	*ft_get_tokens(char *prompt)
{
	t_list	*tokens;

	tokens = NULL;
	while (*prompt)
	{
		ft_skip_spaces(&prompt);
		if (*prompt)
			ft_create_token(&prompt, &tokens);
	}
	return (tokens);
}
