/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/01/08 16:00:43 by randrade         ###   ########.fr       */
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
#define T_WORD 'w'
#define T_QUOTE 'q'
#define T_DOLLAR '$'
#define T_SPACE 's'
#define T_PIPE '|'
#define T_REDIRECT '>'

//	TOKENS_SUBTYPE_CHARS
#define OPERATOR_TOKENS	"|<>"
#define SPACE_TOKENS " \t\r\n\v"

typedef struct	s_builtins
{
    long exit_status;
    char **minishell_env;
    char **export_env;
    bool echo_flag;
}		t_builtins;

typedef struct s_env_var {
    char *key;           // Store just the key (e.g., "SHLVL")
    char *value;         // Store just the value (e.g., "1")
    struct s_env_var *next;
    struct s_env_var *prev;
} t_env_var;

/**
 * @brief Main environment management structure
 */
typedef struct s_env {
    t_env_var *vars;     // Linked list of variables
    int var_count;       // Count of variables
    char **env_array;    
    char **env_export;
} 		t_env;

typedef struct	s_prompt_info
{
	char	*prompt;
	t_env	*env;
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
void	ft_print_double_array(char **array);
int array_size(char **array);
int	ft_strcmp(const char *s1, const char *s2);
char *ft_strjoin3(const char *s1, const char *s2, const char *s3);

//_____________	Builtins ______________

//Init Builtins
void init_variables_builtins(t_builtins *builtins);

//Exit
void  create_exit_code(t_builtins *builtins,char *arr[]);

//cd
void cd_builtin(char *path,t_env *env);
//PWD
void pwd_builtin(void);

//Echo
void handle_echo(char *argv[]);
//Export
char *get_key(char *env);
void handle_export(t_env *env);


//EXPORT FUNCTIONS
int export_env_var(t_env *env, const char *key, const char *value);
void append_env_var(t_env_var **head, t_env_var *new_var);
char *get_value(char *env_str);

//ENV FUNCTIONS
t_env *init_env(char **envp);
t_env_var *create_env_node(char *env_str);
void free_env(t_env *env);
void print_env_list(t_env *env);

//UNSET FUNCTIONS
int unset_env_var(t_env *env,char *key_to_unset);

//_____________	Parsing	______________

//Parsing
t_list	*ft_parsing(t_prompt_info *prompt_info);

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
