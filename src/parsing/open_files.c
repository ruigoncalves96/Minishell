/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:05:53 by randrade          #+#    #+#             */
/*   Updated: 2025/03/28 15:27:45 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//  ------   //   ------
//  REDIRECTIONS FD CODES
//      >= 0 -> EXECUTE RED
//      -1 -> ERROR ON OPEN
//      -2 -> PERMISSION DENIED
//      -3 -> DOESNT EXIST
//      -4 -> DONT EXECUTE

static void	verify_and_open(t_token *token)
{
	if (token->red->type == OUT || token->red->type == A_OUT)
	{
		if (!verify_file_exists(token))
			token->red->fd = open(token->red->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (verify_file_permissions(token))
			token->red->fd = open(token->red->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (token->red->type == IN)
	{
		if (verify_file_exists(token) && verify_file_permissions(token))
			token->red->fd = open(token->red->filename, O_RDONLY);
	}
}

static bool	open_redirect(t_token *token, bool *open_error)
{
	if (!token || !token->red || !token->red->filename)
		return (false);
	if (*open_error)
	{
		token->red->fd = -4;
		return (true);
	}
	verify_and_open(token);
	if (token->next->token[1] != NULL)
	{
		if (get_redirection_files(token) == false)
			return (false);
	}
	if (token->red->fd < 0 && token->red->fd > -4)
		*open_error ^= 1;
	return (true);
}

static bool	open_heredoc(t_token *token, t_prompt_info prompt_info)
{
	if (!token || !token->red || !token->red->filename)
		return (false);
	if (token->next->token[1] != NULL)
	{
		if (get_redirection_files(token) == false)
			return (false);
	}
	else if (!get_heredoc_command_list(token))
		token->red->fd = -4;
	if (get_heredoc_input(token, prompt_info) == false)
		return (false);
	if (token->red->fd != -4)
		token->red->fd = 0;
	return (true);
}

static bool	open_redirections(t_token *token, t_prompt_info prompt_info,
		bool *open_error)
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

bool	loop_and_open_fd(t_token *token, t_prompt_info prompt_info)
{
	bool				open_error;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

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
