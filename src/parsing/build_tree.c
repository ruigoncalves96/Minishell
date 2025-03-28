/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/11 18:01:13 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_tree(t_token *tree)
{
	if (tree->previous && tree->previous->type == OPERATOR)
	{
		if (tree->previous->subtype == T_PIPE && tree->subtype != T_PIPE)
			tree->previous = NULL;
		else
			close_tree(tree->previous);
	}
	else if (tree->previous && tree->previous->type == COMMAND)
	{
		tree->previous->previous = NULL;
		tree->previous->next = NULL;
	}
	if (tree->next && tree->next->type == OPERATOR)
		close_tree(tree->next);
	else if (tree->next && tree->next->type == COMMAND)
	{
		tree->next->previous = NULL;
		tree->next->next = NULL;
	}
}

static void	build_operator_subtree(t_token **subtree, t_token **node)
{
	if (*subtree)
		(*node)->previous = *subtree;
	if ((*node)->previous && (*node)->previous->subtype != T_PIPE)
		(*node)->previous->prev = *node;
	if ((*node)->next && (*node)->next->type == COMMAND)
		(*node)->next->prev = *node;
	*subtree = *node;
	*node = (*node)->next;
}

static t_token	*build_subtree(t_token *list)
{
	t_token	*subtree;
	t_token	*node;

	subtree = NULL;
	node = list;
	while (1)
	{
		node = find_operator(node);
		if (node && node->subtype != T_PIPE)
			build_operator_subtree(&subtree, &node);
		else if (!node || node->subtype == T_PIPE)
		{
			if (subtree)
				return (subtree);
			else
				return (list);
		}
	}
	return (NULL);
}

static void	build_pipe_root(t_token **tree, t_token **top_token,
		t_token **tokens_list)
{
	if (*tree)
	{
		(*top_token)->previous = *tree;
		(*top_token)->previous->prev = *top_token;
	}
	else
	{
		(*top_token)->prev = NULL;
		(*top_token)->previous = build_subtree(*tokens_list);
		(*top_token)->previous->prev = *top_token;
	}
	(*top_token)->next = build_subtree((*top_token)->next);
	if ((*top_token)->next)
		(*top_token)->next->prev = *top_token;
	*tree = *top_token;
}

t_token	*build_tree(t_token *tokens_list)
{
	t_token	*tree;
	t_token	*top_token;

	tree = NULL;
	top_token = tokens_list;
	while (1)
	{
		top_token = find_pipe(top_token);
		if (top_token)
			build_pipe_root(&tree, &top_token, &tokens_list);
		else if (!top_token && !tree)
			tree = build_subtree(tokens_list);
		else
			break ;
	}
	close_tree(tree);
	return (tree);
}
