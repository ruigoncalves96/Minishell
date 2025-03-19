/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:22:31 by randrade          #+#    #+#             */
/*   Updated: 2025/03/03 15:55:43 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_command_array(t_list **node)
{
	char   **new_token;
	size_t array_len;
	size_t i;

	array_len = command_array_len(*node);
	if (array_len == 0)
	    array_len = 1;
	new_token = ft_calloc(array_len + 2, sizeof(char *));
	if (!new_token)
		return (NULL);
	i = 0;
	while (*node && (*node)->type == COMMAND)
	{
	    if ((*node)->str[0] != '\0' || command_array_len(*node) == 0)
		{
		    new_token[i] = ft_strdup((*node)->str);
		    if (new_token[i] == NULL)
	            return (ft_free_double_array(new_token), NULL);
		    i++;
		}
		*node = (*node)->next;
	}
	new_token[i] = NULL;
	return (new_token);
}

static t_redirect *redirect_new(t_list *node, int type)
{
    t_redirect  *red;

    red = ft_calloc(1, sizeof(t_redirect));
    if (!red)
        return (NULL);
    red->fd = -1;
    red->filename = ft_strdup(node->next->str);
    if (!red->filename)
    {
        free(red);
        return (NULL);
    }
    red->type = type;
    return (red);
}

static t_token	*define_redirect_token(t_list **node)
{
	t_token	*new_token;
	char	**new_str;
	int	type;

	type = 0;
	new_str = ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (NULL);
	new_str[0] = ft_strdup((*node)->str);
	if (!new_str[0])
		return (ft_free_double_array(new_str), NULL);
	new_str[1] = NULL;
	type = check_redirect_type(new_str[0]);
	new_token = ft_token_new(OPERATOR, T_REDIRECT, new_str);
	if (!new_token)
		return (ft_free_double_array(new_str), NULL);
	new_token->red = redirect_new(*node, type);
	if (!new_token->red)
		return (free_token_list(new_token), NULL);
	*node = (*node)->next;
	return (new_token);
}

static t_token	*define_pipe_token(t_list **node)
{
	t_token	*new_token;
	char	**new_str;

	new_token = NULL;
	new_str = ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (NULL);
	new_str[0] = ft_strdup("|");
	if (!new_str[0])
		return (ft_free_double_array(new_str), NULL);
	new_str[1] = NULL;
	new_token = ft_token_new(OPERATOR, T_PIPE, new_str);
	if (!new_token)
		return (ft_free_double_array(new_str), NULL);
	*node = (*node)->next;
	return (new_token);
}

t_token	*define_tokens(t_list *prompt_list)
{
	t_token	*token_list;
	t_token	*new_token;
	t_list	*node;

	node = prompt_list;
	token_list = NULL;
	while (node)
	{
		if (node->type == COMMAND)
		{
			char c = (char)node->subtype;
			new_token = ft_token_new(COMMAND, c, get_command_array(&node));
		}
		else
		{
			if (node->subtype == T_PIPE)
				new_token = define_pipe_token(&node);
			else if (node->subtype == T_REDIRECT)
			{
			    if ((!node->previous || node->previous->type != COMMAND) && (node->next && node->next->next && node->next->next->type == COMMAND))
				    ft_token_add_last(&token_list, ft_token_new(COMMAND, T_WORD, NULL));
				new_token = define_redirect_token(&node);
			}
		}
		if (new_token == NULL)
			return (free_token_list(token_list), NULL);
		ft_token_add_last(&token_list, new_token);
	}
	return (token_list);
}
