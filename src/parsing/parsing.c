/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/03/03 14:58:57 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	print_linked_list(t_list *list)
// {
// 	t_list	*temp;

// 	temp = list;
// 	while (temp)
// 	{
// 		ft_printf("token = %s\n", temp->str);
// //		if (temp->previous)
// //			ft_printf("token->previous = %s\n", temp->previous->str);
// //		else
// //			ft_printf("token->previous = NULL\n");
// /*		if (temp->type == COMMAND)
// 			ft_printf("      = type = COMMAND\n");
// 		else if (temp->type == OPERATOR)
// 			ft_printf("      = type = OPERATOR\n");
// 		if (temp->subtype == T_WORD)
// 			ft_printf("      = subtype = WORD\n");
// 		else if (temp->subtype == T_QUOTE)
// 			ft_printf("      = subtype = QUOTE\n");
// 		else if (temp->subtype == T_DOLLAR)
// 			ft_printf("      = subtype = DOLLAR\n");
// 		else if (temp->subtype == T_SPACE)
// 			ft_printf("      = subtype = SPACE\n");
// 		else if (temp->subtype == T_PIPE)
// 			ft_printf("      = subtype = PIPE\n");
// 		else if (temp->subtype == T_REDIRECT)
// 			ft_printf("      = subtype = REDIRECT\n");
// 	*/	temp = temp->next;
// 	}
// }

// void	print_linked_tokens(t_token *list)
// {
// 	t_token *temp;

// 	temp = list;
// 	while (temp)
// 	{
// 		ft_printf("Tokens =\n");
// 		print_double_array(temp->token);
// 		if (temp->previous)
// 			ft_printf("token->previous = %s\n", temp->previous->token[0]);
// 		else
// 			ft_printf("token->previous = NULL\n");
// 		if (temp->type == COMMAND)
// 			ft_printf("      = type = COMMAND\n");
// 		else if (temp->type == OPERATOR)
// 			ft_printf("      = type = OPERATOR\n");
// 		if (temp->subtype == T_WORD)
// 			ft_printf("      = subtype = WORD\n");
// 		else if (temp->subtype == T_QUOTE)
// 			ft_printf("      = subtype = QUOTE\n");
// 		else if (temp->subtype == T_DOLLAR)
// 			ft_printf("      = subtype = DOLLAR\n");
// 		else if (temp->subtype == T_SPACE)
// 			ft_printf("      = subtype = SPACE\n");
// 		else if (temp->subtype == T_PIPE)
// 			ft_printf("      = subtype = PIPE\n");
// 		/*else*/ if (temp->subtype == T_REDIRECT)
// 		{
// 			ft_printf("      = subtype = REDIRECT\n");
// 			ft_printf("		= 	   = 	      = fd = %d\n", temp->red->fd);
// 			ft_printf("		= 	   = 	      = filename = \n");
// 			printf("%s\n", temp->red->filename);
// 			ft_printf("		= 	   = 	      = heredoc = \n");
// 			print_double_array(temp->red->heredoc);
// 			if (temp->red->type == IN)
// 				ft_printf("		= 	   = 	      = type = IN\n");
// 			else if (temp->red->type == OUT)
// 				ft_printf("		= 	   = 	      = type = OUT\n");
// 			else if (temp->red->type == A_OUT)
// 				ft_printf("		= 	   = 	      = type = A_OUT\n");
// 			else if (temp->red->type == HEREDOC)
// 				ft_printf("		= 	   = 	      = type = HEREDOC\n");
// 		}
// 		temp = temp->next;
// 	}
// }

// void	ft_print_token_tree(t_token *tree)
// {
// 	t_token *temp;

// 	temp = tree;
// 	ft_printf("Token = ");
// 	print_double_array(temp->token);
// 	if (temp->prev)
// 		ft_printf("Token->prev = %s\n", temp->prev->token[0]);
// 	else
// 		ft_printf("Token->prev = NULL\n");
// 	// ft_printf("\n");
// 	if (temp->red)
// 	{
// 		 ft_printf("red->filename = ");
// 		printf("%s\n", temp->red->filename);
//         ft_printf("red->fd = %d\n", temp->red->fd);
//         ft_printf("red->type = %d\n", temp->red->type);
//         ft_printf("\n");
// 	}
// 	if (temp->previous)
// 	{
// 		 ft_printf("left = \n");
//         ft_print_token_tree(temp->previous);
//         ft_printf("\n");
// 	}
// 	if (temp->next)
// 	{
//         ft_printf("right = \n");
// 		 ft_print_token_tree(temp->next);
// 		ft_printf("\n");
// 	}
// }

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
