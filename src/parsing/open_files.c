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

static int open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return 1;
    // [X] abrir o arquivo
    // printf("Redirect filename: %s\n", token->red->filename[0]);
    if(token->red->type == OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if(token->red->type == A_OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if(token->red->type == IN)
        token->red->fd = open(token->red->filename[0], O_RDONLY);
    if(token->red->fd == -1)
    {
        //Talvez tenha de dar free no red e na str
        return 1;
    }
    return 0;
}

void loop_and_open_fd(t_token *token)
{
    while (token)
    {
        if(token->next && token->next->subtype == T_REDIRECT)
        {
              if(open_redirect(token->next) == 1)
                    printf("Aconteceu alguma coisa de errado equanto processo de escrever o namefile\n");
        }
        token = token->next;
    }
}
