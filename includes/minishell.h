/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/01/08 14:34:04 by randrade         ###   ########.fr       */
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

//	ERRORS
#define SYNTAX_ERROR "syntax error near unexpected token"

//	TOKEN_TYPE
#define COMMAND 1
#define OPERATOR 2

//	TOKEN_SUBTYPE
#define WORD 'w'
#define QUOTE 'q'
#define DOLLAR '$'
#define SPACE 's'
#define PIPE '|'
#define REDIRECT '>'

//	TOKENS_SUBTYPE_CHARS
#define OPERATOR_TOKENS	"|<>"
#define SPACE_TOKENS " \t\r\n\v"



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
/*
typedef struct	s_command
{
	int	type;
	char	**command;
}		t_command;

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

typedef struct	s_tree_node
{
	int	type;
	int	subtype;
	t_command	command;
	t_redirect	redirect;
	t_pipe		pipe;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}		t_node_tree;
*/
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
bool	ft_parsing(t_prompt_info *prompt_info);

//get_tokens
t_list	*ft_build_tokens_list(char *prompt);

//split_token
char	**ft_split_token(char *s, size_t token_len, int token_type);

//parse_syntax
bool	ft_parse_syntax(t_list *token_list);

//expand_tokens
void	ft_expand_tokens(t_list *token_list);

//parsing_utils
void	ft_quote_mode_switch(char *s, bool *active_quote, char *quote);
void	ft_define_token_type(t_list *token);
int	ft_check_token_type(char c);
int	ft_check_token_subtype(char c);
void	ft_skip_spaces(char **prompt);
void	ft_free_list(t_list *list); //		CHANGE DIRECTORY TO UTILS

//error_handling
void	ft_syntax_error(t_list *token_list, t_list *token);

#endif
