/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2024/12/10 13:23:43 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Library/libft/libft.h"
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <stdbool.h>


typedef struct	s_builtins
{
    long exit_status;
}t_builtins;

//General functions
void free_double_array(char *array[]);
void	ft_print_double_array(char **array);
int array_size(char **array);

        //Bultins
//env
char **copy_envp(char *envp[]);

//Exit
void  create_exit_code(t_builtins *builtins,char *arr[]);

//PWD
void pwd_builtin(void);
#endif
