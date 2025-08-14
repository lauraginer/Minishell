/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:32:56 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/08/14 17:17:37 by jcaro-lo         ###   ########.fr       */
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

# define SUCCESS 0
# define FAILURE 1

extern volatile sig_atomic_t	g_signal;

/* Forward declarations */
typedef struct s_ast_node		t_ast_node;

typedef enum e_token_type
{
	TOKEN_WORD,				/* For commands and arguments */
	TOKEN_PIPE,				/* For '|' */
	TOKEN_REDIR_IN,			/* For '<' */
	TOKEN_REDIR_OUT,		/* For '>' */
	TOKEN_REDIR_APPEND,		/* For '>>' */
	TOKEN_REDIR_HEREDOC,	/* For '<<' */
}	t_token_type;

/*
	S0-> Start. It wait for command or redir
	S1-> After word (Arg or comand)
	S2-> After redir. It wait for word (file or EOF)
	S3-> After redirection file
	S4-> After pipe. It wait for new command or redir
*/
typedef enum e_state
{
	S0,
	S1,
	S2,
	S3,
	S4
}	t_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		type;	/* Token type: WORD, REDIR OR PIPE */
	char				**args;	/* Command arguments("ls", "-l", etc.) */
	struct s_ast_node	*left;	/* Left branch */
	struct s_ast_node	*right;	/* Right branch */
}	t_ast_node;

typedef struct s_ms
{
	t_token		*tokens;		/* First element of the token list */
	t_list		*my_env;		/* copy of the env variables */
	t_ast_node	*f_ast_node;	/* First ast node */
	char		*input;			/* input introduces by the user */
	char		**sub_tokens;	/* It contains the sub tokens
								generated on the expansion */
	int			i;				/* Counter */
	int			exp_f;			/* Flag to confirm there's something
								to expand (' , " , $). It let me know
								if I have to resize the value of the token */
	int			s_quot;			/* flag to check if a char is ' outside of "" */
	int			exit_status;
	int			redir_f;		/* Flag to count the number of the redirections
								during the ast construction */
	char		quot;			/* to define what type of quote
								is the current quote */
}	t_ms;

/*Struct generated to store values of the function check_env_split*/
typedef struct s_checkenv
{
	char	*word;
	int		len;
	t_list	*tmp;
}	t_checkenv;

/* ************************************************************************** */
/*                                   MAIN                                    */
/* ************************************************************************** */

/* driver function */
int			main(int arg, char **argv, char **envp);
/* infinite loop for waiting input */
void		main_loop(t_ms *ms);
/* It copies each env var in a char* inside a linked list */
t_list		*copy_env_var(char **envp);
/* Initializates strcut t_ms */
void		init_ms(t_ms *ms);

/* ************************************************************************** */
/*                               SRC_PARSE                                   */
/* ************************************************************************** */

/* LEXER */
/* It split the input in tokens */
int			lexer(t_ms *ms);
/* It tokenizes operators (<, >, <<, >>, |) */
void		token_operator(t_ms *ms);
/* It tokenizes words */
int			token_word(t_ms *ms, int j);
/* It tokenizes input redir (<, <<) */
void		token_redir_in(t_ms *ms, int j);
/* It tokenizer output redir (>, >>) */
void		token_redir_out(t_ms *ms, int j);

/* SYNTAX CHECKER */
/* AUTOMATA (DFA) to check if the syntax written by the user is correct */
int			syntax_checker(t_ms *ms);
/* It checks the ongoing state to follow the corresponding transition func */
int			syntax_checker2(t_token *aux_t, t_state *st);
/* Transition function from 0 to the next */
int			transit_0(t_token *aux_t, t_state *st);
/* Transition function from 1 or 2 to the next */
int			transit_1_2(t_token *aux_t, t_state *st);
/* Transition function from 3 or 4 to the next */
int			transit_3_4(t_token *aux_t, t_state *st);
/* Function to check if the token is a redirection token */
int			is_redir(t_token *token);

/* EXPANDER */
/* main function to expand variables */
void		expander(t_ms *ms);
/* It joins the subtokens splitted */
void		join_subtokens(t_ms *ms, t_token *aux_t);
/* It splits the token in sub_tokens if needed */
void		split_sub_token(t_ms *ms, t_token *aux_t, int *count);
/* It checks if there's something to expand 
	and start the expansion if needed */
void		start_expand(t_ms *ms, t_token *aux_t, int *count);
/* It tells if there's any quote or $ */
int			is_exp_token(char c);
/* It counts how many subtokens will be created 
	due to the expand (to allocate the memory correctly) */
void		count_subtokens(t_ms *ms, t_token *aux_t, int *count);
/* Second part of count subtokens */
void		count_subtokens2(t_ms *ms, t_token *aux_t, int *count);
/* It counts subtokens created by dolar sign */
void		count_dolar_subtokens(t_ms *ms, t_token *aux_t, int *count, char c);
/* It checks if a given word matches an enviroment
	 variable to count it as subtoken */
void		check_env_count(t_ms *ms, t_token *aux_t, int *count);
/* It split tokens inside simple quotes */
void		split_squot_subt(t_ms *ms, t_token *aux_t, int *count);
/* It split tokens not contained inside $, simple of double quotes */
void		split_norm_subt(t_ms *ms, t_token *aux_t, int *count);
/* It split tokens inside double quotes */
void		split_dquot_subt(t_ms *ms, t_token *aux_t, int *count);
/* It split tokens after dolar sign */
void		split_dolar_subt(t_ms *ms, t_token *aux_t, int *count, char c);
/* Second par of split_dquot_subt */
void		split_dquot_subt2(t_ms *ms, t_token *aux_t, int *count);
/* It checks if a given word matches an enviroment
	 variable to split it as subtoken */
void		check_env_split(t_ms *ms, t_token *aux_t, int *count);
/* Second part of check_env_split */
void		check_env_split2(t_ms *ms, int *count, t_checkenv **check);
/* It replaes env variable by its value */
char		*replace_env(t_ms *ms, t_list *tmp, char **word);

/* AST */
/* Driver function for creating the abstract syntax tree */
t_ast_node	*ast_main(t_ms *ms, t_token *token);
/* It creates a pipe node */
t_ast_node	*ast_pipe(t_ms *ms, t_token *token);
/* It creates a redirection node */
t_ast_node	*ast_redirection(t_ms *ms, t_token *token);
/* It creates a file node */
t_ast_node	*ast_file(t_ms *ms, t_token *token);
/* It creates a command node */
t_ast_node	*ast_cmd(t_ms *ms, t_token *token);
/* It creates and alloc memory for a new node */
t_ast_node	*new_ast_node(t_token_type type, t_ms *ms);
/* It counts how many arguments has a command node */
int			argument_counter(t_token *token);

/* UPDATE SHLVL */
void		increase_shlvl(t_ms *ms);
void		decrease_shlvl(t_ms *ms);

/* FREE PARSE */
/* It frees the linked list of the tokens */
void		free_token_list(t_token *tokens);
/* It frees the subtokens splitted */
void		free_double_char(char **double_char);
/* It frees the abstract syntax tree */
void		free_ast(t_ast_node *ast);

/* UTILS PARSE */
/* It creates a new token node and fills it */
t_token		*lstnew_token(char *value, t_token_type type);
/* It add a token to the back of the list */
void		lstadd_back_token(t_token **tokens, t_token *new);
/* It fills the values of the token node and add it at the end of the list */
void		fill_and_add_token_node(t_ms *ms, t_token_type type, int j);
/* It checks if the char is a redirection or a pipe, and return 1 */
int			is_operator(t_ms *ms);
/* It checks if the char is not allowed, and return 1 in that case */
int			is_not_allowed(t_ms *ms);
/* To print and check tokens (TO BE DELETED LATER) */
void		print_tokens(t_ms *ms);

/* ************************************************************************** */
/*                             SRC_EXECUTE                                   */
/* ************************************************************************** */

/* EXECUTE */
int			execute_ast(t_ast_node *node, t_ms *ms);

/* EXECUTE_CMD */
char		**get_env_arr(t_ms *ms, t_list *my_env);
int			execute_external_command(t_ast_node **args, t_ms **ms,
				t_list *my_env);

/* EXECUTE_PIPE */
int			execute_pipe(t_ast_node *pipe_node, t_ms *ms);

/* HEREDOC */
int			create_heredoc_pipe(char *delimiter, t_ms *ms);
int			process_heredocs(t_ast_node *node, t_ms *ms);

/* PATH_UTILS */
char		*get_env_value(char *name, t_list *my_env);
char		*get_command_path(char *cmd, t_list *my_env);

/* REDIRECTIONS */
int			execute_redirection(t_ast_node *node, t_ms *ms);
int			handle_input(t_ast_node *node, t_ms *ms);
int			handle_output(t_ast_node *node, t_ms *ms);
int			handle_append(t_ast_node *node, t_ms *ms);

/* UTILS_EX */
void		ft_free_split(char **split);
char		*manage_relative_or_absolute_path(char *cmd);
int			is_string_numeric(char *filename);
int			get_input_fd(char *filename, t_ms *ms);

/* UTILS_EX2 */
int			is_empty_line(char *line);
int			check_heredoc_signal(char *line, int pipe_fd[2], t_ms *ms);
int			process_heredoc_line(char *line, char *delimiter, int pipe_fd[2]);
int			read_heredoc_lines(char *delimiter, int pipe_fd[2], t_ms *ms);

/* BUILT-INS */
int			is_builtin(char *cmd);
int			execute_builtin(t_ast_node *node, t_ms *ms);
int			execute_builtin_with_fork(t_ast_node *node, t_ms *ms);
int			needs_parent_execution(char *cmd);
int			builtin_cd(char **args, t_ms *ms);
int			handle_cd_home(t_ms *ms);
int			handle_cd_oldpwd(t_ms *ms);
int			handle_cd_path(char *path, t_ms *ms);
int			builtin_echo(char **args, t_ms *ms);
int			valid_flag(char *str);
void		print_arg(char *arg);
int			builtin_env(char **args, t_list *my_env, t_ms *ms);
int			builtin_exit(char **args, t_ms *ms);
int			control_nums(char *str);
int			builtin_export(char **args, t_list **my_env, t_ms *ms);
int			add_to_env(char *var, t_list **my_env);
int			builtin_pwd(char **args, t_ms *ms);
int			builtin_unset(char **args, t_list **my_env, t_ms *ms);
int			remove_env(char *var, t_list **my_env);
int			ft_strcmp(const char *s1, const char *s2);
int			update_env_var(char *var, t_list **my_env);
int			update_pwd_env(const char *old_dir);
void		print_env(t_list **my_env);
void		debug_ast(t_ast_node *root);
void		free_ms_content(t_ms *ms);
void		free_env_list(t_list *my_env);
void		free_ms(t_ms *ms);
int			is_correct(char *arg);
int			env_exportable(char *var, t_list **my_env);
int			handle_home_cases(void);
int			special_case(char *str);

/* ************************************************************************** */
/*                              SRC_SIGNAL                                   */
/* ************************************************************************** */

/* SIGNALS */
void		signal_handler(int sig);
void		setup_signals(void);
void		signal_logic(void);
void		restore_normal_signals(void);

/* UTILS_SIGNALS */
void		heredoc_signal_handler(int sig);
void		setup_heredoc_signals(void);

#endif