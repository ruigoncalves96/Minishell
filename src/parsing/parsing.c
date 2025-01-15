/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 17:08:54 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_linked_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		ft_printf("token = %s\n", temp->str);
//		if (temp->previous)
//			ft_printf("token->previous = %s\n", temp->previous->str);
//		else
//			ft_printf("token->previous = NULL\n");
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

void	ft_print_linked_tokens(t_token *list)
{
	t_token *temp;

	temp = list;
	while (temp)
	{
		ft_printf("Tokens =\n");
		ft_print_double_array(temp->token);
//		if (temp->previous)
//			ft_printf("token->previous = %s\n", temp->previous->str);
//		else
//			ft_printf("token->previous = NULL\n");
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
		{
			ft_printf("      = subtype = REDIRECT\n");
			ft_printf("	 = 	   = 	      = fd = %d\n", temp->red->fd);
			ft_printf("	 = 	   = 	      = filename = \n");
			ft_print_double_array(temp->red->filename);
			if (temp->red->type == IN)
				ft_printf("	 = 	   = 	      = type = IN\n");
			else if (temp->red->type == OUT)
				ft_printf("	 = 	   = 	      = type = OUT\n");
			else if (temp->red->type == A_OUT)
				ft_printf("	 = 	   = 	      = type = A_OUT\n");
			else if (temp->red->type == HEREDOC)
				ft_printf("	 = 	   = 	      = type = HEREDOC\n");
		}
		temp = temp->next;
	}
}

t_token	*ft_parsing(t_prompt_info *prompt_info)
{
	t_list	*prompt_list;
	t_token	*tokens_list;
	
	tokens_list = NULL;
	prompt_list = ft_build_tokens_list(prompt_info->prompt);
	if (!prompt_list)
		return (NULL);
	if (ft_parse_syntax(prompt_list) == false)
		return (NULL);
	if (ft_expand_vars(prompt_info, &prompt_list) == NULL)
		return (NULL);
	if (ft_convert_quotes(prompt_list) == NULL)
		return (NULL);
	tokens_list = ft_define_tokens(prompt_list);
	ft_free_list(prompt_list);
	if (!tokens_list)
		return (NULL);
	ft_print_linked_tokens(tokens_list);
	return (tokens_list);
}
