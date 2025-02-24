/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/17 17:32:30 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>
#include <unistd.h>

static void    close_repeated_redirections(t_token *token)
{
    if (token->previous && token->previous->previous && token->previous->previous->red)
    {
        if (token->previous->previous->red->type == token->red->type ||
            (token->red->type == HEREDOC && token->previous->previous->red->type == IN))
        {
            if (token->red->type != HEREDOC)
                close(token->previous->previous->red->fd);
            token->previous->previous->red->fd = -1;
        }
    }
}

static bool verify_file_exists(t_token *token)
{
    if (access(token->red->filename[0], F_OK) != 0)
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
        if (access(token->red->filename[0], R_OK) != 0)
        {
            token->red->fd = -2;
            return (false);
        }
    }
    else if (token->red->type == OUT || token->red->type == A_OUT)
    {
        if (access(token->red->filename[0], W_OK) != 0)
        {
            token->red->fd = -2;
            return (false);
        }
    }
    return (true);
}

//  ------   //   ------
//  FD CODES REDS
//      >= 0 -> EXECUTE RED
//      -1 -> ERROR ON OPEN
//      -2 -> PERMISSION DENIED
//      -3 -> DOESNT EXIST
//      -4 -> DONT EXECUTE

static bool open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return (false);
    if (token->red->type == OUT || token->red->type == A_OUT)
    {
        if (!verify_file_exists(token))
            token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (verify_file_permissions(token))
            token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    else if(token->red->type == IN)
    {
        if (verify_file_exists(token) && verify_file_permissions(token))
            token->red->fd = open(token->red->filename[0], O_RDONLY);
    }
    else if (token->red->type == HEREDOC)
    {
        if (token->red->filename[1] != NULL)
        {
            get_redirection_files(token);
            token->red->fd = -4;
        }
        else
            token->red->fd = 0;
        get_heredoc_input(token);
    }
    if (token->red->filename[1] != NULL && token->red->type != HEREDOC)
    {
        get_redirection_files(token);
        if (token->red->type == IN)
            token->red->fd = -4;
    }
    return (true);
}

bool    loop_and_open_fd(t_token *token,t_prompt_info *prompt_info)
{

 //   bool success;

    //success = true;
    while (token)
    {
        if (token->subtype == T_REDIRECT)
        {
            if (open_redirect(token) == false)
            {
                perror(token->red->filename[0]);
                prompt_info->builtins->exit_code = 1;
               //success = false;
                return (false);
            }
            close_repeated_redirections(token);
        }
        token = token->next;
    }
    return (true);
}
