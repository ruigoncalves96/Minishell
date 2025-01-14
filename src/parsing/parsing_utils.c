/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/14 17:37:23 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_quote_len(char *str)
{
	char	quote;
	size_t	i;

	i = 1;
	quote = *str;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_find_var(char *str)
{
	size_t	quote_len;
	bool	double_quote;

	quote_len = 0;
	double_quote = false;
	while (*str)
	{
		if (*str == '"')
			double_quote ^= 1;
		else if (double_quote == false && *str == '\'')
		{
			quote_len += ft_quote_len(str);
			str += quote_len;
		}
		if (*str == '$' && ft_var_key_len(str + 1))
			return (str);
		str++;
	}
	return (NULL);
}

void	ft_define_token_type(t_list *token)
{
	int	subtype;
	int	type;

	subtype = ft_check_token_subtype(*token->str);
	type = ft_check_token_type(*token->str);
	token->type = type;
	token->subtype = subtype;
}

int	ft_check_token_type(char c)
{
	int	subtype;

	subtype = ft_check_token_subtype(c);
	if (subtype == T_WORD || subtype == T_QUOTE || subtype == T_DOLLAR)
		return (COMMAND);
	else if (subtype == T_PIPE || subtype == T_REDIRECT)
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
		return (T_REDIRECT);
	else if (c == T_DOLLAR)
		return (T_DOLLAR);
	else
		return (T_WORD);
}

size_t	ft_strlen_until_spaces(char *str)
{
	size_t	i;
	
	i = 0;
	while (str[i])
	{
		if (ft_check_token_subtype(str[i]) == T_SPACE)
			return (i);
		i++;
	}
	return (i);
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

void	ft_insert_list(t_list **tokens_list, t_list *token, t_list *new_list)
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

//	ADD THIS FUNCTION TO UTILS DIRECTORY
void	ft_free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp);
	}
}
