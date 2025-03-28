/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/17 15:13:23 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_token_type(char c)
{
	int	subtype;

	subtype = check_token_subtype(c);
	if (subtype == T_WORD || subtype == T_QUOTE || subtype == T_DOLLAR)
		return (COMMAND);
	else if (subtype == T_PIPE || subtype == T_REDIRECT)
		return (OPERATOR);
	return (0);
}

int	check_token_subtype(char c)
{
	if (ft_strchr(SPACE_TOKENS, c) != NULL)
		return (T_SPACE);
	else if (c == '"' || c == 39)
		return (T_QUOTE);
	else if (c == '|')
		return (T_PIPE);
	else if (c == '<' || c == '>')
		return (T_REDIRECT);
	else if (c == T_DOLLAR)
		return (T_DOLLAR);
	else
		return (T_WORD);
}

int	check_redirect_type(char *redirect)
{
	int		type;
	size_t	len;

	type = 0;
	len = ft_strlen(redirect);
	if (ft_strncmp(redirect, "<", len) == 0)
		type = IN;
	else if (ft_strncmp(redirect, ">", len) == 0)
		type = OUT;
	else if (ft_strncmp(redirect, ">>", len) == 0)
		type = A_OUT;
	else if (ft_strncmp(redirect, "<<", len) == 0)
		type = HEREDOC;
	return (type);
}
