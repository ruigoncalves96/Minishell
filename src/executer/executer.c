/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:20:26 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/28 18:07:12 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	type_of_executer(t_token *token, t_prompt_info prompt_info)
{
	int	valid;

	if (!token->token[0] || (token->token[0][0] == '\0'
		&& token->subtype != T_QUOTE))
		return ;
	if (is_builtin(*token->token))
		execute_builtin(token, prompt_info, prompt_info.builtins);
	else
	{
		valid = validate_command_path(*token->token, prompt_info.env);
		if (valid == 0)
			executer_manager(token->token, prompt_info, token);
		else
			prompt_info.builtins->exit_code = valid;
	}
}

void	runcmd(t_token *token, t_prompt_info prompt_info)
{
	if (!token)
		return ;
	if (token->type == OPERATOR)
	{
		if (token->subtype == T_PIPE)
			pipe_executer(token, prompt_info);
		else if (token->subtype == T_REDIRECT)
		{
			if (token->red->type == HEREDOC)
				heredoc_executer(token, prompt_info);
			else
				redirections_executer(token, prompt_info);
		}
	}
	else if (token->type == COMMAND)
		type_of_executer(token, prompt_info);
}

void	loop_executer(t_token *token_head, t_prompt_info prompt_info)
{
	t_token	*token;
	int		original_fd[2];

	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
	if (original_fd[0] == -1 || original_fd[1] == -1)
	{
		if (original_fd[0] != -1)
			close(original_fd[0]);
		if (original_fd[1] != -1)
			close(original_fd[1]);
		return ;
	}
	token = token_head;
	if (!token->next)
		type_of_executer(token, prompt_info);
	else
		runcmd(token, prompt_info);
	dup2(original_fd[0], STDIN_FILENO);
	dup2(original_fd[1], STDOUT_FILENO);
	close(original_fd[0]);
	close(original_fd[1]);
	if (prompt_info.builtins->exit_code % 128 == SIGINT
		&& prompt_info.builtins->exit_code > 128)
		write(1, "\n", 1);
}
