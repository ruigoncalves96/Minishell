/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/17 17:32:30 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool verify_file_exists(t_token *token)
{
    if (access(token->red->filename, F_OK) != 0)
    {
        token->red->fd = -3;
        return (false);
    }
    return (true);
}

bool verify_file_permissions(t_token *token)
{
    if (token->red->type == IN)
    {
        if (access(token->red->filename, R_OK) != 0)
        {
            token->red->fd = -2;
            return (false);
        }
    }
    else if (token->red->type == OUT || token->red->type == A_OUT)
    {
        if (access(token->red->filename, W_OK) != 0)
        {
            token->red->fd = -2;
            return (false);
        }
    }
    return (true);
}

void    close_repeated_redirections(t_token *token)
{
    t_token *previous;

    previous = NULL;
    if (token->previous && token->previous->previous && token->previous->previous->red)
        previous = token->previous->previous;
    else
        return ;
    if (((token->red->type == OUT || token->red->type == A_OUT) && (previous->red->type == OUT || previous->red->type == A_OUT))
            || ((token->red->type == HEREDOC || token->red->type == IN) && (token->red->type == HEREDOC || token->red->type == IN)))
    {
        if (previous->red->type != HEREDOC && token->red->fd >= 0)
            close(previous->red->fd);
        if (previous->red->fd >= 0 || previous->red->type == HEREDOC)
            previous->red->fd = -4;
    }
}
