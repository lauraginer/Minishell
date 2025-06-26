/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:18 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/26 18:27:00 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

#define SUCCESS 0
#define FAILURE 1

typedef enum e_token_type
{
    TOKEN_WORD,      // For commands and arguments
    TOKEN_S_QUOTES,  // For what's inside simple quotes
	TOKEN_PIPE,      // For '|'
    TOKEN_REDIR_IN,  // For '<'
    TOKEN_REDIR_OUT, // For '>'
    TOKEN_REDIR_APPEND, // For '>>'
    TOKEN_REDIR_HEREDOC, // For '<<'
}   t_token_type;

typedef enum e_node_type
{
    NODE_CMD,  
    NODE_PIPE, 
    NODE_REDIR_IN,
    NODE_REDIR_OUT,
    NODE_REDIR_APPEND,
    NODE_REDIR_HEREDOC,
    NODE_ENV_VAR,
}   t_node_type;

typedef struct s_token
{
    t_token_type type;
    char        *value;
    struct s_token *next;
}   t_token;

typedef struct s_parse
{
	t_token	*tokens;
	char	*input;
	int		count;
}	t_parse;

typedef struct s_ast_node
{
    t_node_type type;             // Tipo del nodo: comando, pipe, redirección, etc.
    char *args;                   // Argumentos del comando (por ejemplo, "ls", "-l", etc.)
    struct s_ast_node *left;      // Hijo izquierdo (ej: primer comando en un pipe)
    struct s_ast_node *right;     // Hijo derecho (ej: segundo comando en un pipe)
}   t_ast_node;


//MAIN

/*driver function*/
int		main(int arg, char **argv, char **envp);
/*infinite loop for waiting input*/
void	main_loop(t_parse *parse, t_list *my_env);
/*It copies each env var in a char* inside a linked list*/
t_list	*copy_env_var(char **envp);

//PARSER

/*Initializates strcut t_parse*/
t_parse *init_parse();
/*It split the input in tokens*/
int		lexer(t_list *my_env, t_parse *parse);
/*Filter to save what's inside quotes*/
int		quot_filt(t_parse *parse, t_list *my_env, char c, t_token_type type);
/*It fills the values of the token node and add it at the end of the list*/
int		fill_and_add_token_node(t_parse *parse, t_list *my_env, t_token_type type, int j);

//EXECUTE

//builtins
int		builtin_echo(char **args);
int		valid_flag(char *str);
void	print_arg(char *arg);
int		builtin_cd(char **args);
int		builtin_pwd(char **args);
int		control_nums(char *str);
int		builtin_exit(char **args);
int		builtin_env(char **args, t_list *my_env);
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		is_builtin(char *cmd);
int		execute_builtin(char **args);

//FREE

/*It frees the linked list of env vars*/
void	free_env_list(t_list *my_env);
/*It frees the linked list of the tokens*/
void	free_token_list(t_token *tokens);
/*It frees the struct parse*/
void	free_parse(t_parse *parse);

//utils

/*It creates a new token node and fills it*/
t_token	*lstnew_token(char *value, t_token_type type);
/*It add a token to the back of the list*/
void	lstadd_back_token(t_token **tokens, t_token *new);


#endif