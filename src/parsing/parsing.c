/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/08 16:15:11 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print_linked_list(t_list *list)
{
	t_list	*temp;
	int	i;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->str[i])
		{
			ft_printf("token[%d] = %s\n", i, temp->str[i]);
			i++;
		}
		if (temp->type == COMMAND)
			ft_printf("      = type = COMMAND\n");
		else if (temp->type == OPERATOR)
			ft_printf("      = type = OPERATOR\n");
		if (temp->subtype == T_WORD)
			ft_printf("      = subtype = WORD\n");
		else if (temp->subtype == T_QUOTE)
			ft_printf("      = subtype = QUOTE\n");
		else if (temp->subtype == T_DOLLAR)
			ft_printf("      = subtype = DOLLAR\n");
		else if (temp->subtype == T_SPACE)
			ft_printf("      = subtype = SPACE\n");
		else if (temp->subtype == T_PIPE)
			ft_printf("      = subtype = PIPE\n");
		else if (temp->subtype == T_REDIRECT)
			ft_printf("      = subtype = REDIRECT\n");
		temp = temp->next;
	}
}

t_list	*ft_parsing(t_prompt_info *prompt_info)
{
	t_list	*tokens;
	
	tokens = ft_build_tokens_list(prompt_info->prompt);
	if (ft_parse_syntax(tokens) == false)
		return (NULL);
	//	CONVERT QUOTES && EXPAND DOLLAR
//	ft_expand_tokens(tokens);
	//	BUILD TREE
//	ft_print_linked_list(tokens);
//	ft_free_list(tokens);
	return (tokens);
}
