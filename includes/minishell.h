/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/01/04 17:22:54 by randrade         ###   ########.fr       */
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

#define OPERATOR 'o'
#define SPACE 's'
#define QUOTE 'q'
#define WORD 'a'

#define EXECUTER 1
#define REDIRECT 2
#define PIPE 3

typedef struct	s_builtins
{
	long	exit_status;
	bool	echo_flag;
}		t_builtins;

typedef struct	s_prompt_info
{
	char	*prompt;
	char	**env;
}		t_prompt_info;

typedef struct	s_branch
{
	int	type;
	void	*left;
	void	*right;
}		t_branch;

typedef struct	s_executer
{
	int	type;
	char	**command;
}		t_executer;

typedef struct	s_redirect
{
	int	type;
	int	fd;
	char	*filename;
	void	**command;
}		t_redirect;

typedef struct	s_pipe
{
	int	type;
	void	*left;
	void	*right;
}		t_pipe;

//General functions
void free_double_array(char *array[]);
void	ft_print_double_array(char **array);
int array_size(char **array);

//_____________	Builtins ______________

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

//_____________	Parsing	______________

//Parsing
void	ft_parsing(t_prompt_info *prompt_info);

//get_tokens
t_list	*ft_get_tokens(char *prompt);

//parsing_utils
void	ft_skip_spaces(char **prompt);
void	ft_free_list(t_list *list);

#endif
