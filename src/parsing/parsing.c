/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/04 17:15:37 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print_linked_list(t_list *list)
{
	while (list)
	{
		ft_printf("token = %s\n", list->str);
		list = list->next;
	}
}

void	ft_parsing(t_prompt_info *prompt_info)
{
	t_list	*tokens;
	
	tokens = ft_get_tokens(prompt_info->prompt);
	ft_print_linked_list(tokens);
	// BUILD TREE
	ft_free_list(tokens);	
}
