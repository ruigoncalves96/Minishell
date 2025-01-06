/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/06 15:04:46 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_define_token(t_list *token)
{
	if (token->type == WORD || token->type == QUOTE)
		token->type = EXECUTER;
	else if (token->type == OPERATOR)
	{
		if (token->str[0][0] == '|')
			token->type = PIPE;
		else if (token->str[0][0] == '>' || token->str[0][0] == '<')
			token->type = REDIRECT;
	}
}

void	ft_quote_mode_switch(char s, bool *active_quote, char *quote)
{
	if (s == '"' || s == 39)
	{
		if (*active_quote == false)
			*quote = s;
		if (s == *quote)
		{
			*active_quote ^= 1;
			if (*active_quote == false)
				*quote = 0;
		}
	}
}

char	ft_check_token(char c)
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

void	ft_skip_spaces(char **prompt)
{
	while (**prompt)
	{
		if (**prompt != ' ' && **prompt != '\t' && **prompt != '\r' &&
				**prompt != '\n' && **prompt != '\v')
			break ;
		(*prompt)++;
	}
}

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
