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
    char **minishell_env;
    char **export_env;
    bool echo_flag;
}t_builtins;

//General functions
void free_double_array(char *array[]);
void	ft_print_double_array(char **array);
int array_size(char **array);
int	ft_strcmp(const char *s1, const char *s2);

        //Bultins
//env
char **copy_envp(char *envp[]);
void flag_env();

//Exit
void  create_exit_code(t_builtins *builtins,char *arr[]);

//cd
void cd_builtin(char *path);

//PWD
void pwd_builtin(void);

//Echo
void echo(char **arr, bool echo_flag);
void handle_echo(int argc, char *argv[]);

//Export
char *get_key(char *env);
void sort_env_ascii_order(char **env);
void print_x_declaration(char **env);
void handle_export(char **export_env);
int export_variable(t_builtins *vars, char *key_to_find, char *new_value);
//
#endif
