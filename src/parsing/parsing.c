/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/06 17:29:39 by randrade         ###   ########.fr       */
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
		if (temp->type == 1)
			ft_printf("      = type = COMMAND\n");
		else if (temp->type == 2)
			ft_printf("      = type = REDIRECT\n");
		else if (temp->type == 3)
			ft_printf("      = type = PIPE\n");
		temp = temp->next;
	}
}



void	ft_parsing(t_prompt_info *prompt_info)
{
	t_list	*tokens;
	
	tokens = ft_get_tokens(prompt_info->prompt);
	ft_print_linked_list(tokens);
	//	PARSE SYNTAX NODE TYPE
	//		| -> cmd1 | cmd2 = CORRECT / | cmd = INCORRECT / cmd | = INCORRECT
	//		< > << >> -> < filename = CORRECT / cmd < filename = CORRECT / cmd > = INCORRECT
	//		general rule -> no operators next to another
	//	
	//	BUILD TREE
	ft_free_list(tokens);
}
