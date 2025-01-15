/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:10:54 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 16:52:53 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_parse_pipe(t_list *token)
{
	if ((token->previous && token->previous->type == COMMAND)
		&& ((token->next && token->next->type == COMMAND)
		|| (token->next && token->next->subtype == T_REDIRECT)))
		return (true);
	return (false);
}

static bool	ft_parse_redirect(t_list *token)
{
	if (token->next && token->next->type == OPERATOR)
		return (false);
	else if (!token->next)
		return (false);
	return (true);
}

static bool	ft_parse_operator(t_list *token)
{
	if (token->subtype == T_PIPE)
	{
		if (ft_parse_pipe(token) == false)
			return (false);
	}
	else if (token->subtype == T_REDIRECT)
	{
		if (ft_parse_redirect(token) == false)
			return (false);
	}
	return (true);
}

bool	ft_parse_syntax(t_list *token_list)
{
	t_list	*token;

	token = token_list;
	while (token) 
	{
		if (token->type == OPERATOR)
		{
			if (ft_parse_operator(token) == false)
			{
				ft_syntax_error(token_list, token);
				return (false);
			}
		}
		token = token->next;
	}
	return (true);
}

//	PARSE SYNTAX NODE TYPE
	//		| -> cmd1 | cmd2 = CORRECT / | cmd = INCORRECT / cmd | = INCORRECT
	//		< > << >> -> < filename = CORRECT / cmd < filename = CORRECT / cmd > = INCORRECT
	//		general rule -> no operators next to another
