/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/03 17:55:41 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_get_tokens(char *str)
{
	// CREATE LINKED LIST WITH TOKENS SEPARATED
}

void	ft_parsing(t_prompt_info *prompt_info)
{
	t_list	*tokens;
	
	tokens = ft_get_tokens(prompt_info->prompt);
	// BUILD TREE
}
