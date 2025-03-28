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

char	*find_expand_dollar(char *str, bool *double_quote, bool heredoc)
{
	if (heredoc == true)
	{
		while (*str)
		{
			if (*str == '$')
			{
				if (var_key_len(str + 1))
					return (str);
			}
			str++;
		}
		return (NULL);
	}
	while (*str)
	{
		if (*str == '"')
			*double_quote ^= 1;
		else if (*double_quote == false && *str == '\'')
			str += quote_len(str) + 1;
		if (*str == '$' && ((check_token_subtype(*(str + 1)) == T_QUOTE
					&& *double_quote == false) || var_key_len(str + 1)))
			return (str);
		str++;
	}
	return (NULL);
}

t_token	*find_operator(t_token *list)
{
	while (list)
	{
		if (list->type == OPERATOR)
			return (list);
		else
			list = list->next;
	}
	return (NULL);
}

t_token	*find_pipe(t_token *list)
{
	if (list && list->subtype == T_PIPE)
		list = list->next;
	while (list)
	{
		if (list->subtype == T_PIPE)
			return (list);
		else
			list = list->next;
	}
	return (NULL);
}

void	skip_spaces(char **prompt)
{
	while (**prompt)
	{
		if (ft_strchr(SPACE_TOKENS, **prompt) == NULL)
			break ;
		(*prompt)++;
	}
}

void	insert_list(t_list **tokens_list, t_list *token, t_list *new_list)
{
	t_list	*temp;

	temp = new_list;
	new_list->previous = token->previous;
	if (token->previous)
		token->previous->next = new_list;
	else
		*tokens_list = new_list;
	temp = ft_lstlast(temp);
	temp->next = token->next;
	if (token->next)
		token->next->previous = temp;
	free(token->str);
	free(token);
	token = NULL;
}
