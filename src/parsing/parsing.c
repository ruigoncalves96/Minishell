/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2026/08/20 15:50:42 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*parsing(t_prompt_info *prompt_info)
{
	t_list	*prompt_list;
	t_token	*tokens_tree;

	tokens_tree = NULL;
	prompt_list = build_tokens_list(prompt_info->prompt);
	if (!prompt_list)
		return (NULL);
	if (parse_syntax(prompt_list, prompt_info) == false)
		return (NULL);
	if (expand_vars(*prompt_info, &prompt_list) == NULL)
		return (NULL);
	if (convert_quotes(prompt_list) == NULL)
		return (NULL);
	tokens_tree = define_tokens(prompt_list);
	free_list(prompt_list);
	if (!tokens_tree)
		return (NULL);
	if (loop_and_open_fd(tokens_tree, *prompt_info) == false)
		return (free_token_list(tokens_tree), NULL);
	tokens_tree = build_tree(tokens_tree);
	return (tokens_tree);
}
