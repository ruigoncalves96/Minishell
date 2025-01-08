/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/08 15:46:09 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quote_mode_switch(char *c, bool *active_quote, char *quote)
{
	if ((*c == '"' || *c == 39) && (*c == *quote || *active_quote == false))
	{
		if (*active_quote == false)
		{
			if (ft_strchr(c + 1, *c) == NULL)
				return ;
			else
				*quote = *c;
		}
		else
			*quote = 0;
		*active_quote ^= 1;
	}
}

void	ft_define_token_type(t_list *token)
{
	int	subtype;
	int	type;

	subtype = ft_check_token_subtype(token->str[0][0]);
	type = ft_check_token_type(token->str[0][0]);
	token->type = type;
	token->subtype = subtype;
}

int	ft_check_token_type(char c)
{
	int	subtype;

	subtype = ft_check_token_subtype(c);
	if (subtype == T_WORD || subtype == T_QUOTE || subtype == T_DOLLAR)
		return (COMMAND);
	else if (subtype == T_PIPE || subtype == REDIRECT)
		return (OPERATOR);
	return (0);
}

int	ft_check_token_subtype(char c)
{
	if (ft_strchr(SPACE_TOKENS, c) != NULL)
		return (T_SPACE);
	else if (c == '"' || c == 39)
		return (T_QUOTE);
	else if (c == '|')
		return (T_PIPE);
	else if (c == '<' || c == '>')
		return (REDIRECT);
	else if (c == T_DOLLAR)
		return (T_DOLLAR);
	else
		return (T_WORD);
}

void	ft_skip_spaces(char **prompt)
{
	while (**prompt)
	{
		if (ft_strchr(SPACE_TOKENS, **prompt) == NULL)
			break ;
		(*prompt)++;
	}
}

//	ADD THIS FUNCTION TO UTILS DIRECTORY
void	ft_free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		ft_free_double_array(temp->str);
		free(temp);
	}
}
