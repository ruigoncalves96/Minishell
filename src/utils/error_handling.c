/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:19:15 by randrade          #+#    #+#             */
/*   Updated: 2025/01/11 01:34:56 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quote_error()
{
	ft_putstr_fd(QUOTE_ERROR, 2);
	ft_putstr_fd("\n", 2);
}

void	syntax_error(t_list *token_list, t_list *token)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putstr_fd(" `", 2);
	if (token->subtype != T_PIPE && !token->next)
	    ft_putstr_fd("newline", 2);
	else if (token->subtype == T_PIPE)
	    ft_putstr_fd(token->str, 2);
	else
	    ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd("'\n", 2);
	free_list(token_list);
}
