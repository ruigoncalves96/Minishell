/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:19:15 by randrade          #+#    #+#             */
/*   Updated: 2025/01/07 20:36:08 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_syntax_error(t_list *token_list, t_list *token)
{
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(*token->str, 2);
	ft_putstr_fd("'\n", 2);
	ft_free_list(token_list);
}
