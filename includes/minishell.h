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

typedef struct s_env_var {
    char *key;           // Store just the key (e.g., "SHLVL")
    char *value;         // Store just the value (e.g., "1")
    struct s_env_var *next;
} t_env_var;

/**
 * @brief Main environment management structure
 */
typedef struct s_env {
    t_env_var *vars;     // Linked list of variables
    int var_count;       // Count of variables
    char **env_array;    // Traditional env array format
    char **env_export;
} t_env;

//New env functions
t_env *init_env(char **envp);
t_env_var *create_env_node(char *env_str);
void free_env(t_env *env);
void print_env_list(t_env *env);



//General functions
void free_double_array(char *array[]);
void	ft_print_double_array(char **array);
int array_size(char **array);
int	ft_strcmp(const char *s1, const char *s2);
char *ft_strjoin3(const char *s1, const char *s2, const char *s3);

        //Bultins

//Init Builtins
void init_variables_builtins(t_builtins *builtins, char *env[]);
void free_variables_builtins(t_builtins *vars);
//env
char **copy_envp(char *envp[]);
void flag_env();
void print_env(char *env[],bool flag);
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
    //Exporting variables
char **create_new_env(char **old_env, int size);
int add_new_variable(t_builtins *vars, char *new_value, int size);
int update_existing_var(t_builtins *vars, char *key_to_find, 
    char *new_value, char *key);
int export_variable(t_builtins *vars, char *key_to_find, char *new_value);
    //Unset
int unset_variable(t_builtins *vars, char *key_to_remove);
#endif
