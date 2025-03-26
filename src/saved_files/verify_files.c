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

static bool verify_file_exists(t_token *token)
{
    if (access(token->red->filename, F_OK) != 0)
    {
        token->red->fd = -3;
        return (false);
    }
    return (true);
}

static bool verify_file_permissions(t_token *token)
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

void    verify_and_open_file(t_token *token)
{
    if (token->red->type == OUT || token->red->type == A_OUT)
    {
        if (!verify_file_exists(token) || verify_file_permissions(token))
            token->red->fd = open(token->red->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    else if(token->red->type == IN)
    {
        if (verify_file_exists(token) && verify_file_permissions(token))
            token->red->fd = open(token->red->filename, O_RDONLY);
    }
}
