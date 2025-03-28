/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:12:10 by hguerrei          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:20 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// HANDLE FIND VAR ALLOC FREE IF ERROR MALLOC
static char	*expand_vars_heredoc(char *heredoc, t_prompt_info prompt_info)
{
	char	*var_value;
	char	*dollar;
	size_t	expanded_str_len;

	var_value = NULL;
	expanded_str_len = 0;
	while (1)
	{
		dollar = heredoc;
		dollar += expanded_str_len;
		dollar = find_expand_dollar(heredoc, NULL, true);
		if (!dollar)
			break ;
		var_value = find_var_value(prompt_info, dollar);
		expanded_str_len = ft_strlen(var_value)
			+ strlen_until_expansion(heredoc, dollar);
		heredoc = join_var(heredoc, var_value, dollar, var_key_len(dollar + 1));
		if (!heredoc)
			return (NULL);
	}
	return (heredoc);
}

static bool	handle_heredoc_exit(t_token *token, t_prompt_info *prompt_info,
		char *heredoc, int pipefd)
{
	if (!heredoc || g_heredoc_c_pressed)
	{
		if (g_heredoc_c_pressed)
		{
			cleanup_all(prompt_info, NULL);
			free_token_list(token);
			close(pipefd);
			prompt_info->builtins->exit_code = 130;
			exit(prompt_info->builtins->exit_code);
		}
		else
			print_error("minishell", NULL, EOF_H, 0);
		return (true);
	}
	return (false);
}

static bool	is_eof(t_token *token, char *heredoc)
{
	if (ft_strcmp(heredoc, token->red->filename) == 0)
	{
		free(heredoc);
		return (true);
	}
	return (false);
}

static bool	handle_heredoc_input(t_token *token, t_prompt_info *prompt_info,
		char *heredoc, int pipefd)
{
	if (token->next->subtype != T_QUOTE && token->next->token[1] == NULL)
	{
		heredoc = expand_vars_heredoc(heredoc, *prompt_info);
		if (!heredoc)
			return (false);
	}
	ft_putstr_fd(heredoc, pipefd);
	ft_putstr_fd("\n", pipefd);
	free(heredoc);
	return (true);
}

void	readline_heredoc(t_token *token, t_prompt_info *prompt_info, int pipefd)
{
	char	*heredoc;

	heredoc = NULL;
	while (1)
	{
		heredoc = readline("> ");
		if (handle_heredoc_exit(token, prompt_info, heredoc, pipefd) == true)
			break ;
		if (is_eof(token, heredoc) == true)
			break ;
		if (handle_heredoc_input(token, prompt_info, heredoc, pipefd) == false)
			handle_heredoc_exit(token, prompt_info, heredoc, pipefd);
	}
	close(pipefd);
	if (g_heredoc_c_pressed)
	{
		free_token_list(token);
		cleanup_all(prompt_info, NULL);
		exit(130);
	}
	free_token_list(token);
	cleanup_all(prompt_info, NULL);
	exit(0);
}
