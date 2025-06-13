/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:18 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/13 19:26:02 by lginer-m         ###   ########.fr       */
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

typedef enum e_token_type
{
    TOKEN_WORD,      // For commands and arguments
    TOKEN_PIPE,      // For '|'
    TOKEN_REDIR_IN,  // For '<'
    TOKEN_REDIR_OUT, // For '>'
    TOKEN_REDIR_APPEND, // For '>>'
    TOKEN_REDIR_HEREDOC, // For '<<'
    TOKEN_ENV_VAR, // For environment variables
}   t_token_type;

typedef struct s_token
{
    t_token_type type;
    char        *value;
    struct s_token *next;
}   t_token;

typedef struct s_ast_node
{
    t_node_type type;             // Tipo del nodo: comando, pipe, redirección, etc.
    char *args;                   // Argumentos del comando (por ejemplo, "ls", "-l", etc.)
    struct s_ast_node *left;      // Hijo izquierdo (ej: primer comando en un pipe)
    struct s_ast_node *right;     // Hijo derecho (ej: segundo comando en un pipe)
}   t_ast_node;


//builtins
int builtin_echo(char **args);
int builtin_cd(char **args);
int builtin_pwd(char **args);
int builtin_exit(char **args);
int builtin_env(char **envp);
int builtin_export(char **args);
int builtin_unset(char **args);
int is_builtin(char *cmd);
int execute_builtin(char **args);

#endif