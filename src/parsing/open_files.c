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

static void    close_repeated_redirections(t_token *token)
{
    if (token->previous && token->previous->previous && token->previous->previous->red)
    {
        if (token->previous->previous->red->type == token->red->type)
        {
            if (token->red->type != HEREDOC)
                close(token->previous->previous->red->fd);
           token->previous->previous->red->fd = -1;
        }
    }
}

static bool open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return (false);
    // printf("Redirect filename: %s\n", token->red->filename[0]);
    if(token->red->type == OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if(token->red->type == A_OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if(token->red->type == IN)
        token->red->fd = open(token->red->filename[0], O_RDONLY);
    else if (token->red->type == HEREDOC)
    {
        if (token->red->filename[1] != NULL)
            get_heredoc_files(token);
        get_heredoc_input(token);
        token->red->fd = 0;
    }
    if(token->red->fd == -1)
    {
        //Talvez tenha de dar free no red e na str
        return (false);
    }
    return (true);
}

bool    loop_and_open_fd(t_token *token)
{
    while (token)
    {
        if (token->subtype == T_REDIRECT)
        {
            if (open_redirect(token) == false)
            {
                printf("Aconteceu alguma coisa de errado equanto processo de escrever o namefile\n");
                return (false);
            }
            close_repeated_redirections(token);
        }
        token = token->next;
    }
    return (true);
}
