/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:18 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/22 09:52:39 by jcaro-lo         ###   ########.fr       */
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
/*Initializates strcut t_parse*/
t_parse *init_parse();

//LEXER

/*It split the input in tokens*/
int		lexer(t_list *my_env, t_parse *parse);
/*Filter to save what's inside quotes*/
int		quot_filt(t_parse *parse, t_list *my_env, char c, t_token_type type);
/*It tokenizes operators (<, >, <<, >>, |)*/
void	token_operator(t_list *my_env, t_parse *parse);
/*It tokenizes everything except quotes*/
int		token_not_quot(t_list *my_env, t_parse *parse);
/*It tokenizes input redir (<, <<)*/
void	token_redir_in(t_list *my_env, t_parse *parse, int j);
/*AÑADIR A .h:It tokenizer output redir (>, >>)*/
void	token_redir_out(t_list *my_env, t_parse *parse, int j);


//EXECUTE

//builtins
int		builtin_echo(char **args);
int		valid_flag(char *str);
void	print_arg(char *arg);
int		builtin_cd(char **args);
int		builtin_pwd(char **args);
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

//UTILS

/*It creates a new token node and fills it*/
t_token	*lstnew_token(char *value, t_token_type type);
/*It add a token to the back of the list*/
void	lstadd_back_token(t_token **tokens, t_token *new);
/*It fills the values of the token node and add it at the end of the list*/
void	fill_and_add_token_node(t_parse *parse, t_list *my_env, t_token_type type, int j);
/*It checks if the char is a redirection or a pipe, and return 1 in that case*/
int		is_operator(t_parse *parse);
/*It checks if the char is not allowed, and return 1 in that case*/
int		is_not_allowed(t_parse *parse);


/*Para imprimir y chequear los tokens (HAY QUE BORRARLA LUEGO)*/
void print_tokens(t_parse *parse);

#endif