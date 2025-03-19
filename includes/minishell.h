/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/03/17 14:46:52 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Library/libft/libft.h"
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>

//	ERRORS
#define QUOTE_ERROR "syntax error unclosed quote"
#define SYNTAX_ERROR "syntax error near unexpected token"
#define TOO_MANY_ARGS "too many arguments"
#define ERROR_OPENING_FILE "Error on opening redirect file"
#define NO_FILE_OR_DIRECTORY "No such file or directory"
//exit
#define	EXIT_NUMERIC_ERROR "numeric argument required"
//cd
#define HOME_NOT_SET "HOME not set"
//commands
#define DIRECTORY "Is a directory"
#define COMMAND_NOT_FOUND "command not found"
#define PERMISSION_DENIED "Permission denied"
//export
#define NOT_VALID_IDENTIFIER "not a valid identifier"

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

extern volatile sig_atomic_t heredoc_c_pressed;

void handler_heredoc(int sig);

typedef struct	s_builtins
{
    bool echo_flag;
	int	 exit_code;
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
	t_builtins *builtins;
}		t_prompt_info;

typedef struct s_list
{
	char           *str;
	int            type;
	int	           subtype;
	struct s_list  *previous;
	struct s_list  *next;
}				t_list;

typedef struct s_redirect
{
	int    fd;
	char   *filename;
	char   **heredoc;
	int    type;
}		t_redirect;

typedef struct s_token
{
	char           **token;
	int            type;
	int            subtype;
	t_redirect     *red;
	struct s_token *prev;
	struct s_token *previous;
	struct s_token *next;
}				t_token;

//_____________	Utils ______________

//General functions
void	print_double_array(char **array);
int array_size(char **array);
int	ft_strcmp(const char *s1, const char *s2);
void print_error(const char *cmd, const char *arg, const char *msg,bool print_bash);
t_token	*go_to_tree_top(t_token *token);

//List_struct_functions
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst);
void	ft_lstadd_last(t_list **lst, t_list *new_node);
void	ft_lstadd_first(t_list **lst, t_list *new_node);
t_list	*ft_lstnew(char *content);

//Token_struct_functions
t_token	*ft_token_last(t_token *token);
void	ft_token_delone(t_token *token);
void	ft_token_add_last(t_token **token, t_token *new_token);
void	ft_token_add_first(t_token **token, t_token *new_token);
t_token	*ft_token_new(int type, char subtype, char **content);

//Free_structs
void	free_list(t_list *list);
void	free_token_list(t_token *tokens_list);
void    free_token_tree(t_token *token_tree);


//_____________	Builtins ______________

//Init Builtins
void init_variables_builtins(t_builtins *builtins);
int is_builtin(char *cmd);
int execute_builtin(t_token *tokens, t_prompt_info prompt_info,t_builtins *builtins);
void update_shlvl(t_env *env);
//Exit
void exit_manager(char **args, t_builtins *builtins,t_prompt_info *prompt_info,t_token *tokens);
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

int export_manager(char **str, t_env *env,t_builtins *builtins);
//ENV FUNCTIONS
t_env *init_env(char **envp);
t_env_var *create_env_node(char *env_str);
void free_env(t_env *env);
void print_env_list(t_env *env);
//UNSET FUNCTIONS
int unset_env_var(t_env *env,char *key_to_unset);
int manager_unset(char **str, t_env *env);


//_____________	Executing______________

//prepare_path
char **convert_env_to_array(t_env *env);
char *get_env_value(t_env *env,const char *key);
char *get_command_path(char *command, t_env *env);
int validate_command_path(char *command, t_env *env);

//redirections
void runcmd(t_token *token, t_env *env, t_prompt_info prompt_info);
void    loop_executer(t_token *token_head, t_env *env, t_prompt_info prompt_info);
int executer_manager(char **str, t_env *env,t_prompt_info prompt_info,t_token *token);
void close_fds();
//heredoc
bool    get_heredoc_input(t_token *token, t_prompt_info prompt_info);
void    get_redirection_files(t_token *token);
void    heredoc_executer(t_token *token, t_env *env, t_prompt_info prompt_info);
t_token    *get_heredoc_command_list(t_token *token);

//signals
void    set_signals(void);

//_____________	Parsing	______________

//Parsing
void	print_linked_list(t_list *list);
void	print_linked_tokens(t_token *list);
t_token	*parsing(t_prompt_info *prompt_info);

//get_tokens
t_list	*build_tokens_list(char *prompt);

//parse_syntax
bool	parse_syntax(t_list *token_list,t_prompt_info *prompt_info);

//convert_quotes
t_list	*convert_quotes(t_list *tokens_list);

//expand_vars
char	*join_var(char *token_str, char *var_value, char *var_key_pos, size_t key_len);
t_list	*expand_vars(t_prompt_info prompt_info, t_list **tokens_list);

//define_tokens
t_token	*define_tokens(t_list *prompt_list);

//build_tree
t_token *build_tree(t_token *tokens_list);

//open_files
bool    loop_and_open_fd(t_token *token,t_prompt_info prompt_info);

//find_var_value
size_t	var_key_len(char *str);
char	*find_var_value(t_prompt_info prompt_info, char *dollar);

//parsing_utils
size_t	quote_len(char *str);
char	*find_expand_dollar(char *str, bool *double_quotes);
int	check_token_type(char c);
int	check_token_subtype(char c);
int	check_redirect_type(char *redirect);
size_t	strlen_until_spaces(char *str);
void	skip_spaces(char **prompt);
void	insert_list(t_list **tokens_list, t_list *token, t_list *new_list);
size_t	command_array_len(t_list *node);

//error_handling
void	quote_error();
void	syntax_error(t_list *token_list, t_list *token);

#endif
