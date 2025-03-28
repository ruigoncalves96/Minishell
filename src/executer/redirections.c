/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:21:54 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/28 15:21:55 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_redirection_file(t_token *token, t_prompt_info prompt_info)
{
	if (token->red->fd == -1)
		print_error(NULL, token->red->filename, ERROR_OPENING_FILE, true);
	else if (token->red->fd == -2)
		print_error(NULL, token->red->filename, PERMISSION_DENIED, true);
	else if (token->red->fd == -3)
		print_error(NULL, token->red->filename, NO_FILE_OR_DIRECTORY, true);
	prompt_info.builtins->exit_code = 1;
}

static void	execute_redirection(t_token *token, t_prompt_info prompt_info)
{
	if ((token->red->type == OUT || token->red->type == A_OUT)
		&& token->red->fd != -4)
	{
		if (dup2(token->red->fd, STDOUT_FILENO) == -1)
		{
			prompt_info.builtins->exit_code = 1;
			perror("dup2");
			close_fds();
			exit(1);
		}
		close(token->red->fd);
		token->red->fd = -4;
	}
	else if (token->red->type == IN && token->red->fd != -4)
	{
		if (dup2(token->red->fd, STDIN_FILENO) == -1)
		{
			prompt_info.builtins->exit_code = 1;
			perror("dup2");
			close_fds();
			exit(1);
		}
		close(token->red->fd);
		token->red->fd = -4;
	}
}

void	redirections_executer(t_token *token, t_prompt_info prompt_info)
{
	if (token->red->fd < 0 && token->red->fd != -4)
	{
		error_redirection_file(token, prompt_info);
		return ;
	}
	execute_redirection(token, prompt_info);
	if (token->previous && token->previous->type == COMMAND
		&& (token->red->fd >= 0 || token->red->fd == -4))
		type_of_executer(token->previous, prompt_info);
	else if (token->previous && token->previous->type == OPERATOR)
		runcmd(token->previous, prompt_info);
}
