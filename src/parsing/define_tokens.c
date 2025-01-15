/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:22:31 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 16:43:52 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_get_command_array(t_list **node)
{
	char	**new_token;
	size_t	i;

	new_token = ft_calloc(ft_command_array_len(*node) + 1, sizeof(char *));
	if (!new_token)
		return (NULL);
	i = 0;
	while (*node && (*node)->type == COMMAND)
	{
		new_token[i] = ft_strdup((*node)->str);
		if (new_token[i] == NULL)
			return (ft_free_double_array(new_token), NULL);
		i++;
		*node = (*node)->next;
	}
	new_token[i] = NULL;
	return (new_token);
}

static t_redirect	*ft_redirect_new(t_list *node, int type)
{
	t_redirect	*red;
	
	node = node->next;
	red = ft_calloc(1, sizeof(t_redirect));
	if (!red)
		return (NULL);
	red->fd = -1;
	red->filename = ft_get_command_array(&node);
	if (!red->filename)
		return (free(red), NULL);
	red->type = type;
	return (red);
}

static t_token	*ft_define_redirect_token(t_list *node)
{
	t_token	*new_token;
	char	**new_str;
	int	type;

	type = 0;
	new_str = ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (NULL);
	new_str[0] = ft_strdup(node->str);
	if (!new_str[0])
		return (ft_free_double_array(new_str), NULL);
	new_str[1] = NULL;
	type = ft_check_redirect_type(new_str[0]);
	new_token = ft_token_new(new_str, OPERATOR, T_REDIRECT);
	if (!new_token)
		return (ft_free_double_array(new_str), NULL);
	new_token->red = ft_redirect_new(node, type);
	if (!new_token->red)
		return (ft_free_token_list(new_token), NULL);
	return (new_token);
}

static t_token	*ft_define_pipe_token()
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
	new_token = ft_token_new(new_str, OPERATOR, T_PIPE);
	if (!new_token)
		return (ft_free_double_array(new_str), NULL);
	return (new_token);
}

t_token	*ft_define_tokens(t_list *prompt_list)
{
	t_token	*token_list;
	t_token	*new_token;
	t_list	*node;

	node = prompt_list;
	token_list = NULL;
	while (node)
	{
		if (node->type == COMMAND)
			new_token = ft_token_new(ft_get_command_array(&node), COMMAND, T_WORD);
		else
		{
			if (node->subtype == T_PIPE)
				new_token = ft_define_pipe_token();
			else if (node->subtype == T_REDIRECT)
				new_token = ft_define_redirect_token(node);
			node = node->next;
		}
		if (new_token == NULL)
			return (ft_free_token_list(token_list), NULL);
		ft_token_add_last(&token_list, new_token);
	}
	return (token_list);
}
