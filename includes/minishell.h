/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/03/28 17:51:18 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
# include "../Library/libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

//	ERRORS
# define QUOTE_ERROR "syntax error unclosed quote"
# define SYNTAX_ERROR "syntax error near unexpected token"
# define TOO_MANY_ARGS "too many arguments"
# define ERROR_OPENING_FILE "Error on opening redirect file"
# define NO_FILE_OR_DIRECTORY "No such file or directory"
// exit
# define EXIT_NUMERIC_ERROR "numeric argument required"
// cd
# define HOME_NOT_SET "HOME not set"
// commands
# define DIRECTORY "Is a directory"
# define COMMAND_NOT_FOUND "command not found"
# define PERMISSION_DENIED "Permission denied"
// export
# define NOT_VALID_IDENTIFIER "not a valid identifier"
// heredoc
# define EOF_H "warning: here-document delimited by end-of-file (wanted `EOF')"

//	TOKEN_TYPE
# define COMMAND 1
# define OPERATOR 2

//	TOKEN_SUBTYPE
# define T_WORD 'w'
# define T_QUOTE 'q'
# define T_DOLLAR '$'
# define T_SPACE 's'
# define T_PIPE '|'
# define T_REDIRECT '>'
//	TOKENS_SUBTYPE_CHARS
# define OPERATOR_TOKENS "|<>"
# define SPACE_TOKENS " \t\r\n\v"

//	REDIRECT_TYPES
# define IN 1
# define OUT 2
# define A_OUT 3
# define HEREDOC 4

extern volatile sig_atomic_t	g_heredoc_c_pressed;

typedef struct s_builtins
{
	bool						echo_flag;
	int							exit_code;
}								t_builtins;

typedef struct s_env_var
{
	char						*key;
	char						*value;
	int							is_export_only; // 1 only export, 0 in both
	struct s_env_var			*next;
	struct s_env_var			*prev;
}								t_env_var;

typedef struct s_env
{
	t_env_var					*vars;
	int							var_count;
}								t_env;

typedef struct s_prompt_info
{
	char						*prompt;
	t_env						*env;
	t_builtins					*builtins;
}								t_prompt_info;

typedef struct s_list
{
	char						*str;
	int							type;
	int							subtype;
	struct s_list				*previous;
	struct s_list				*next;
}								t_list;

typedef struct s_redirect
{
	int							fd;
	char						*filename;
	char						**heredoc;
	int							type;
}								t_redirect;

typedef struct s_token
{
	char						**token;
	int							type;
	int							subtype;
	t_redirect					*red;
	struct s_token				*prev;
	struct s_token				*previous;
	struct s_token				*next;
}								t_token;

/*
				_   _ _____ ___ _     ____
				| | | |_   _|_ _| |   / ___|
				| | | | | |  | || |   \___ \
				| |_| | | |  | || |___ ___) |
				\___/  |_| |___|_____|____/
*/

// Cleanup_all
void							cleanup_all(t_prompt_info *prompt_info,
									t_token *tokens);
void							close_fds(void);
void							init_variables_builtins(t_builtins *builtins);

// Free_struct
void							free_list(t_list *list);
void							free_token_list(t_token *tokens_list);
void							free_token_tree(t_token *token_tree);

// General_functions
void							print_double_array(char **array);
int								array_size(char **array);
int								ft_strcmp(const char *s1, const char *s2);
void							print_error(const char *cmd, const char *arg,
									const char *msg, bool print_bash);
t_token							*go_to_tree_top(t_token *token);

// General_functions_2
size_t							lst_size(t_list *list);
size_t							array_len(char **array);

// List_struct_functions
t_list							*ft_lstlast(t_list *lst);
void							ft_lstdelone(t_list *lst);
void							ft_lstadd_last(t_list **lst, t_list *new_node);
void							ft_lstadd_first(t_list **lst, t_list *new_node);
t_list							*ft_lstnew(char *content);

// Token_struct_functions
t_token							*ft_token_last(t_token *token);
void							ft_token_delone(t_token *token);
void							ft_token_add_last(t_token **token,
									t_token *new_token);
void							ft_token_add_first(t_token **token,
									t_token *new_token);
t_token							*ft_token_new(int type, char subtype,
									char **content);

// parsing_utils
size_t							quote_len(char *str);
size_t							strlen_until_expansion(char *str, char *dollar);
size_t							strlen_until_spaces(char *str);
size_t							command_array_len(t_list *node);

// parsing_utils_2
char							*find_expand_dollar(char *str,
									bool *double_quotes, bool heredoc);
t_token							*find_operator(t_token *list);
t_token							*find_pipe(t_token *list);
void							skip_spaces(char **prompt);
void							insert_list(t_list **tokens_list, t_list *token,
									t_list *new_list);

// parsing_utils_3
int								check_token_type(char c);
int								check_token_subtype(char c);
int								check_redirect_type(char *redirect);

// error_handling
void							quote_error(void);
void							syntax_error(t_list *token_list, t_list *token);

/*
				____  _   _ ___ _   _____ ___ _   _ ____
				| __ )| | | |_ _| | |_   _|_ _| \ | / ___|
				|  _ \| | | || || |   | |  | ||  \| \___ \
				| |_) | |_| || || |___| |  | || |\  |___) |
				|____/ \___/|___|_____|_| |___|_| \_|____/
*/

// cd
int								cd_manager(char **str, t_env *env);

// Echo
void							handle_echo(char *argv[]);

// Env_utils
void							print_env_list(t_env *env);
void							update_shlvl(t_env *env);
void							free_env(t_env *env);

// Exit
void							exit_manager(char **args, t_builtins *builtins,
									t_prompt_info *prompt_info,
									t_token *tokens);

// Exit_utils
int								ft_atol(const char *str, long *result);

// Init Builtins
int								is_builtin(char *cmd);
int								execute_builtin(t_token *tokens,
									t_prompt_info prompt_info,
									t_builtins *builtins);
char							**convert_env_to_array(t_env *env);

// Manager_export
int								export_manager(char **str, t_env *env,
									t_builtins *builtins);

// Manager_unset
int								unset_env_var(t_env *env, char *key_to_unset);
int								manager_unset(char **str, t_env *env);

// New_env
t_env_var						*create_env_node(char *env_str);
void							append_env_var(t_env_var **head,
									t_env_var *new_var);
t_env							*init_env(char **envp);

// new_export
void							handle_export(t_env *env);

// New_export_utils
t_env_var						*copy_env_list(t_env_var *list);

// New_export_variables
void							set_export_only(t_env *env, const char *key,
									int is_export_only);
int								export_env_var(t_env *env, const char *key,
									const char *value, int is_export_only);

// Pwd
void							pwd_builtin(void);

// Utils_buitlins
void							print_error(const char *cmd, const char *arg,
									const char *msg, bool print_bash);
char							*get_key(char *env);
char							*get_value(char *env_str);
char							*get_env_value(t_env *env, const char *key);

/*
				_______  _______ ____ _   _ _____ ___ _   _  ____
				| ____\ \/ / ____/ ___| | | |_   _|_ _| \ | |/ ___|
				|  _|  \  /|  _|| |   | | | | | |  | ||  \| | |  _
				| |___ /  \| |__| |___| |_| | | |  | || |\  | |_| |
				|_____/_/\_\_____\____|\___/  |_| |___|_| \_|\____|
*/

// executer
void							type_of_executer(t_token *token,
									t_prompt_info prompt_info);
void							runcmd(t_token *token,
									t_prompt_info prompt_info);
void							loop_executer(t_token *token_head,
									t_prompt_info prompt_info);

// execve
int								executer_manager(char **str,
									t_prompt_info prompt_info, t_token *token);

// Handle_path_errors
int								validate_command_path(char *command,
									t_env *env);

// heredoc
void							heredoc_executer(t_token *token,
									t_prompt_info prompt_info);

// pipe
int								pipe_executer(t_token *token,
									t_prompt_info prompt_info);

// prepare_path
char							*get_command_path(char *command, t_env *env);

// redirections
void							redirections_executer(t_token *token,
									t_prompt_info prompt_info);

// signals
void							handler_heredoc(int sig);
void							set_signals(void);

// utils_exec
t_token							*get_heredoc_command_tree(t_token *token);
t_token							*get_heredoc_command_list(t_token *token);
void							close_pipes(int pipes[2]);
int								get_exit_status(int status);

/*
				____   _    ____  ____ ___ _   _  ____
				|  _ \ / \  |  _ \/ ___|_ _| \ | |/ ___|
				| |_) / _ \ | |_) \___ \| ||  \| | |  _
				|  __/ ___ \|  _ < ___) | || |\  | |_| |
				|_| /_/   \_\_| \_\____/___|_| \_|\____|
*/

// Parsing
void							print_linked_list(t_list *list);
void							print_linked_tokens(t_token *list);
t_token							*parsing(t_prompt_info *prompt_info);

// get_tokens
t_list							*build_tokens_list(char *prompt);

// parse_syntax
bool							parse_syntax(t_list *token_list,
									t_prompt_info *prompt_info);

// convert_quotes
t_list							*convert_quotes(t_list *tokens_list);

// expand_vars
char							*join_var(char *token_str, char *var_value,
									char *var_key_pos, size_t key_len);
t_list							*expand_vars(t_prompt_info prompt_info,
									t_list **tokens_list);

// define_tokens
t_token							*define_tokens(t_list *prompt_list);

// get_command_array
char							**get_command_array(t_list **node);

// build_tree
t_token							*build_tree(t_token *tokens_list);

// open_files
bool							loop_and_open_fd(t_token *token,
									t_prompt_info prompt_info);

// get_redirection_files
bool							get_redirection_files(t_token *token);

// get_heredoc_input
bool							get_heredoc_input(t_token *token,
									t_prompt_info prompt_info);

// readline_heredoc
void							readline_heredoc(t_token *token,
									t_prompt_info *prompt_info, int pipefd);

// find_var_value
size_t							var_key_len(char *str);
char							*find_var_value(t_prompt_info prompt_info,
									char *dollar);

// verify_files
bool							verify_file_permissions(t_token *token);
bool							verify_file_exists(t_token *token);
void							close_repeated_redirections(t_token *token);

#endif
