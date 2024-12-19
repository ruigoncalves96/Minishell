/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2024/12/19 16:32:25 by randrade         ###   ########.fr       */
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
    bool echo_flag;
}t_builtins;

typedef struct	s_prompt_info
{
	char	*prompt;
	char	**env;
//	t_tokens	tokens;
}		t_prompt_info;

//General functions
void free_double_array(char *array[]);
void	ft_print_double_array(char **array);
int array_size(char **array);

        //Bultins
//env
char **copy_envp(char *envp[]);

//Exit
void  create_exit_code(t_builtins *builtins,char *arr[]);

//cd
void cd_builtin(char *path);

//PWD
void pwd_builtin(void);

//Echo
void echo(char **arr, bool echo_flag);
void handle_echo(int argc, char *argv[]);

	//Parsing
void	ft_parsing(t_prompt_info *prompt_info);

#endif
