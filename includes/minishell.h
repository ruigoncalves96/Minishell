/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 16:56:38 by randrade         ###   ########.fr       */
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
#define QUOTE_ERROR "syntax error unclosed quote"
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

//	REDIRECT_TYPES
#define	IN 1
#define	OUT 2
#define A_OUT 3
#define	HEREDOC 4

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
} 		t_env_var;

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

typedef struct s_list
{
	char			*str;
	int			type;
	int			subtype;
	struct s_list		*previous;
	struct s_list		*next;
}				t_list;

typedef struct s_redirect
{
	int	fd;
	char	**filename;
	int	type;
}		t_redirect;

typedef struct s_token
{
	char			**token;
	int			type;
	int			subtype;
	t_redirect		*red;
	struct s_token		*previous;
	struct s_token		*next;
}				t_token;

//_____________	Utils ______________

//General functions
void	ft_print_double_array(char **array);
int array_size(char **array);
int	ft_strcmp(const char *s1, const char *s2);
char *ft_strjoin3(const char *s1, const char *s2, const char *s3);

//List_struct_functions
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst);
void	ft_lstadd_last(t_list **lst, t_list *new);
void	ft_lstadd_first(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *content);

//Token_struct_functions
t_token	*ft_token_last(t_token *token);
void	ft_token_delone(t_token *token);
void	ft_token_add_last(t_token **token, t_token *new);
void	ft_token_add_first(t_token **token, t_token *new);
t_token	*ft_token_new(char **content, int type, char subtype);

//Free_structs
void	ft_free_list(t_list *list);
void	ft_free_token_list(t_token *tokens_list);


//_____________	Builtins ______________

//env
char **copy_envp(char *envp[]);

//Init Builtins
void init_variables_builtins(t_builtins *builtins);
//void free_variables_builtins(t_builtins *vars);
//env
//char **copy_envp(char *envp[]);
//void flag_env();
//void print_env(char *env[],bool flag);
//Exit
void  create_exit_code(t_builtins *builtins,char *arr[]);

//cd
void cd_builtin(char *path);

//PWD
void pwd_builtin(void);

//Echo
void handle_echo(int argc, char *argv[]);

//Export
char *get_key(char *env);
void sort_env_ascii_order(char **env);
void print_x_declaration(char **env);
void handle_export(char **export_env);
    //Exporting variables
char **create_new_env(char **old_env, int size);
int add_new_variable(t_builtins *vars, char *new_value, int size);
int update_existing_var(t_builtins *vars, char *key_to_find, 
    char *new_value, char *key);
int export_variable(t_builtins *vars, char *key_to_find, char *new_value);
    //Unset
int unset_variable(t_builtins *vars, char *key_to_remove);

//New env functions
t_env *init_env(char **envp);
t_env_var *create_env_node(char *env_str);
void free_env(t_env *env);
void print_env_list(t_env *env);

//new export functions
int export_env_var(t_env *env, const char *key, const char *value);
int env_to_array(t_env *env);
void append_env_var(t_env_var **head, t_env_var *new_var);
char *get_value(char *env_str);

//_____________	Parsing	______________

//Parsing
void	ft_print_linked_list(t_list *list);
void	ft_print_linked_tokens(t_token *list);
t_list	*ft_parsing(t_prompt_info *prompt_info);

//get_tokens
t_list	*ft_build_tokens_list(char *prompt);

//parse_syntax
bool	ft_parse_syntax(t_list *token_list);

//convert_quotes
t_list	*ft_convert_quotes(t_list *tokens_list);

//expand_vars
t_list	*ft_expand_vars(t_prompt_info *prompt_info, t_list **tokens_list);

//define_tokens
t_token	*ft_define_tokens(t_list *prompt_list);

//find_var_value
size_t	ft_var_key_len(char *str);
char	*ft_find_var_value(t_env_var *env, char *str);

//parsing_utils
size_t	ft_quote_len(char *str);
char	*ft_find_var(char *str);
void	ft_define_token_type(t_list *token);
int	ft_check_token_type(char c);
int	ft_check_token_subtype(char c);
int	ft_check_redirect_type(char *redirect);
size_t	ft_strlen_until_spaces(char *str);
void	ft_skip_spaces(char **prompt);
void	ft_insert_list(t_list **tokens_list, t_list *token, t_list *new_list);
size_t	ft_command_array_len(t_list *node);

//error_handling
void	ft_quote_error();
void	ft_syntax_error(t_list *token_list, t_list *token);

#endif
