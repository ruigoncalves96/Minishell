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
#include <stdio.h>

//  ------   //   ------
//  FD CODES REDS
//      >= 0 -> EXECUTE RED
//      -1 -> ERROR ON OPEN
//      -2 -> PERMISSION DENIED
//      -3 -> DOESNT EXIST
//      -4 -> DONT EXECUTE

static void    close_repeated_redirections(t_token *token)
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

static bool open_redirect(t_token *token, bool *open_error)
{
    if (!token || !token->red || !token->red->filename)
        return (false);
    if (*open_error)
    {
        token->red->fd = -4;
        return (true);
    }
    verify_and_open_file(token);
    if (token->next->token[1] != NULL)
    {
        get_redirection_files(token);
        // if (token->red->type == IN)
        //     token->red->fd = -4;
    }
    if (token->red->fd < 0 && token->red->fd > -4)
        *open_error ^= 1;
    return (true);
}

static bool open_heredoc(t_token *token, t_prompt_info prompt_info)
{
    if (!token || !token->red || !token->red->filename)
        return (false);
    if (token->next->token[1] != NULL)
        get_redirection_files(token);
    else if (!get_heredoc_command_list(token))
        token->red->fd = -4;
    if (get_heredoc_input(token, prompt_info) == false)
        return (false);
    if (token->red->fd != -4)
        token->red->fd = 0;
    return (true);
}

static bool    open_redirections(t_token *token, t_prompt_info prompt_info, bool *open_error)
{
    if (token->red->type != HEREDOC)
    {
        if (open_redirect(token, open_error) == false)
        {
            perror(token->red->filename);
            prompt_info.builtins->exit_code = 1;
            return (false);
        }
    }
    else if (token->red->type == HEREDOC)
    {
        if (open_heredoc(token, prompt_info) == false)
        {
            if (prompt_info.builtins->exit_code != 130)
            {
                perror(token->red->filename);
                prompt_info.builtins->exit_code = 1;
            }
            return (false);
        }
    }
    close_repeated_redirections(token);
    return (true);
}

bool    open_files(t_token *token, t_prompt_info prompt_info)
{
    bool    open_error;
    struct sigaction sa_old;
    struct sigaction sa_new;

    sigemptyset(&sa_new.sa_mask);
    sa_new.sa_flags = 0;
    sa_new.sa_handler = SIG_DFL;
    sigaction(SIGINT, NULL, &sa_old);
    open_error = false;
    while (token)
    {
        if (token->subtype == T_PIPE && open_error == true)
            open_error = false;
        else if (token->subtype == T_REDIRECT)
        {
            if (open_redirections(token, prompt_info, &open_error) == false)
                return (false);
        }
        token = token->next;
    }
    sigaction(SIGINT, &sa_old, NULL);
    return (true);
}
