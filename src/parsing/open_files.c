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

//  ------   //   ------
//  FD CODES REDS
//      >= 0 -> EXECUTE RED
//      -1 -> ERROR ON OPEN
//      -2 -> PERMISSION DENIED
//      -3 -> DOESNT EXIST
//      -4 -> DONT EXECUTE

static bool open_redirect(t_token *token, bool *open_error)
{
    if (!token || !token->red || !token->red->filename)
        return (false);
    if (token->red->type == OUT || token->red->type == A_OUT)
    {
        if (!verify_file_exists(token))
            token->red->fd = open(token->red->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (verify_file_permissions(token))
            token->red->fd = open(token->red->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    else if(token->red->type == IN)
    {
        if (verify_file_exists(token) && verify_file_permissions(token))
            token->red->fd = open(token->red->filename, O_RDONLY);
    }
    if (token->next->token[1] != NULL)
    {
        get_redirection_files(token);
        if (token->red->type == IN)
            token->red->fd = -4;
    }
    if (token->red->fd < 0 && token->red->fd > -4)
        *open_error ^= 1;
    return (true);
}

static bool open_redirect_heredoc(t_token *token, t_prompt_info prompt_info)
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

bool    loop_and_open_fd(t_token *token, t_prompt_info prompt_info)
{
    bool    open_error;
    struct sigaction sa_old;
    struct sigaction sa_new;

    //Setup signal
    sigemptyset(&sa_new.sa_mask);
    sa_new.sa_flags = 0;
    sa_new.sa_handler = SIG_DFL;

    //Salva sinal anterior
    sigaction(SIGINT, NULL, &sa_old);
    open_error = false;
    while (token)
    {
        if (token->subtype == T_PIPE && open_error == true)
            open_error = false;
        if (token->subtype == T_REDIRECT && token->red->type != HEREDOC && open_error == false)
        {
            if (open_redirect(token, &open_error) == false)
            {
                perror(token->red->filename);
                prompt_info.builtins->exit_code = 1;
                return (false);
            }
            close_repeated_redirections(token);
        }
        else if (token->subtype == T_REDIRECT && token->red->type == HEREDOC)
        {
            if (open_redirect_heredoc(token, prompt_info) == false)
            {
                perror(token->red->filename);
                prompt_info.builtins->exit_code = 1;
                return (false);
            }
            close_repeated_redirections(token);
        }
        token = token->next;
    }
    //restore no sinalcl
    sigaction(SIGINT, &sa_old, NULL);
    return (true);
}
