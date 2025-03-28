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

static bool	parse_pipe(t_list *token)
{
	if ((token->previous && token->previous->type == COMMAND) && ((token->next
				&& token->next->type == COMMAND) || (token->next
				&& token->next->subtype == T_REDIRECT)))
		return (true);
	return (false);
}

static bool	parse_redirect(t_list *token)
{
	if (token->next && token->next->type == OPERATOR)
		return (false);
	else if (!token->next)
		return (false);
	return (true);
}

static bool	parse_operator(t_list *token)
{
	if (token->subtype == T_PIPE)
	{
		if (parse_pipe(token) == false)
			return (false);
	}
	else if (token->subtype == T_REDIRECT)
	{
		if (parse_redirect(token) == false)
			return (false);
	}
	return (true);
}

bool	parse_syntax(t_list *token_list, t_prompt_info *prompt_info)
{
	t_list	*token;

	token = token_list;
	while (token)
	{
		if (token->type == OPERATOR)
		{
			if (parse_operator(token) == false)
			{
				syntax_error(token_list, token);
				prompt_info->builtins->exit_code = 2;
				return (false);
			}
		}
		token = token->next;
	}
	return (true);
}
