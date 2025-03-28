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

size_t	quote_len(char *str)
{
	char	quote;
	size_t	i;

	i = 0;
	quote = *str;
	str++;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

size_t	strlen_until_expansion(char *str, char *dollar)
{
	size_t	i;

	i = 0;
	if (!str || !dollar)
		return (0);
	while (str[i])
	{
		if (&str[i] == dollar)
			return (i);
		i++;
	}
	return (i);
}

size_t	strlen_until_spaces(char *str)
{
	size_t	i;
	bool	quotes;

	i = 0;
	quotes = false;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			quotes ^= 1;
		if (quotes == true)
			i += quote_len(&str[i]);
		else if (check_token_subtype(str[i]) == T_SPACE)
			return (i);
		i++;
	}
	return (i);
}

size_t	command_array_len(t_list *node)
{
	size_t	nbr_commands;

	nbr_commands = 0;
	while (node && node->type == COMMAND)
	{
		if (node->str[0] != '\0' || (node->str[0] == '\0'
				&& node->subtype == T_QUOTE))
			nbr_commands++;
		else if (node->str[0] == '\0' && node->subtype != T_QUOTE
			&& (!node->previous && !node->next))
			nbr_commands++;
		node = node->next;
	}
	return (nbr_commands);
}
