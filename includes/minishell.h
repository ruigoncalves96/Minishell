/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/01/16 14:14:35 by randrade         ###   ########.fr       */
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
#include <sys/wait.h>


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
    bool echo_flag;
}		t_builtins;

typedef struct s_env_var {
    char *key;           // Store just the key (e.g., "SHLVL")
    char *value;         // Store just the value (e.g., "1")
	int is_export_only; //  1 so aparece no export, 0 aparece no env e no export
    struct s_env_var *next;
    struct s_env_var *prev;
} t_env_var;

/**
 * @brief Main environment management structure
 */
typedef struct s_env {
    t_env_var *vars;     // Linked list of variables
    int var_count;       // Count of variables
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

//Init Builtins
void init_variables_builtins(t_builtins *builtins);
int is_builtin(char *cmd);
int execute_builtin(t_token *tokens, t_prompt_info prompt_info);
void update_shlvl(t_env *env);
//Exit
void exit_manager(char **args,t_prompt_info	prompt_info,t_token		*tokens);
void cleanup_all(t_prompt_info *prompt_info, t_token *tokens);
//cd
int cd_manager(char **str, t_env *env);
//PWD
void pwd_builtin(void);

//Echo
void handle_echo(char *argv[]);
//Export
char *get_key(char *env);
void handle_export(t_env *env);


//EXPORT FUNCTIONS
int export_env_var(t_env *env, const char *key, const char *value,int is_export_only);
void append_env_var(t_env_var **head, t_env_var *new_var);
char *get_value(char *env_str);
void set_export_only(t_env *env, const char *key, int is_export_only);

int export_manager(char **str,t_env *env);
//ENV FUNCTIONS
t_env *init_env(char **envp);
t_env_var *create_env_node(char *env_str);
void free_env(t_env *env);
void print_env_list(t_env *env);

//UNSET FUNCTIONS
int unset_env_var(t_env *env,char *key_to_unset);
int manager_unset(char **str, t_env *env);


//_____________	Executing______________
char **convert_env_to_array(t_env *env);
char *get_env_value(t_env *env,const char *key);
char *get_command_path(char *command, t_env *env);
int validate_command_path(char *command, t_env *env);
void loop_executer(t_token *token, t_env *env, t_prompt_info prompt_info);

int executer_manager( char **str,t_env *env);


//_____________	Parsing	______________

//Parsing
void	ft_print_linked_list(t_list *list);
void	ft_print_linked_tokens(t_token *list);
t_token	*ft_parsing(t_prompt_info *prompt_info);

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
char	*ft_find_var(char *str, bool *double_quotes);
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
