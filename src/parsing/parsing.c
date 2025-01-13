/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/13 17:23:23 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static */void	ft_print_linked_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		ft_printf("token = %s\n", temp->str);
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
	t_list	*tokens_list;
	
	tokens_list = ft_build_tokens_list(prompt_info->prompt);
	if (!tokens_list)
		return (NULL);
	if (ft_parse_syntax(tokens_list) == false)
		return (NULL);
	ft_expand_vars(prompt_info, &tokens_list);
	if (ft_convert_quotes(tokens_list) == NULL)
		return (NULL);
	//	FINISH TOKENS;
	ft_print_linked_list(tokens_list);
	return (tokens_list);
}
