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

static t_token  *find_operator(t_token *list)
{
    while (list)
    {
        if (list->type == OPERATOR)
            return (list);
        else
            list = list->next;
    }
    return (NULL);
}

static t_token  *find_pipe(t_token *list)
{
    while (list)
    {
        if (list->subtype == T_PIPE)
            return (list);
        else
            list = list->next;
    }
    return (NULL);
}

static void close_tree(t_token *tree)
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

static t_token  *build_subtree(t_token *list)
{
    t_token *subtree;
    t_token *node;

    subtree = NULL;
    node = list;
    while (1)
    {
        node = find_operator(node);
        if (node && node->subtype != T_PIPE)
        {
            if (subtree)
                node->previous = subtree;
            subtree = node;
            node = node->next;
        }
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

t_token *build_tree(t_token *tokens_list)
{
    t_token *tree;
    t_token *top_token;

    tree = NULL;
    top_token = tokens_list;
    while(1)
    {
        top_token = find_pipe(top_token);
        if (top_token)
        {
            if (tree)
                top_token->previous = tree;
            else
                top_token->previous = build_subtree(tokens_list);
            top_token->next = build_subtree(top_token->next);
            tree = top_token;
            top_token = top_token->next;
        }
        else if (!top_token && !tree)
            tree = build_subtree(tokens_list);
        else
            break ;
    }
    close_tree(tree);
    return (tree);
}
