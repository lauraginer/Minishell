
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

typedef enum e_token_type
{
	TOKEN_WORD,				// For commands and arguments
	TOKEN_PIPE,				// For '|'
	TOKEN_REDIR_IN,			// For '<'
	TOKEN_REDIR_OUT,		// For '>'
	TOKEN_REDIR_APPEND,		// For '>>'
	TOKEN_REDIR_HEREDOC,	// For '<<'
}	t_token_type;

/*
	SO-> Start. It wait for command or redir
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
}		t_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		type;	//Token type: WORD, REDIR OR PIPE
	char				**args;	//Command arguments("ls", "-l", etc.)
	struct s_ast_node	*left;	//Left branch
	struct s_ast_node	*right;	//Right branch
}	t_ast_node;

typedef struct s_ms
{
	t_token		*tokens;		//First element of the token list
	t_list		*my_env;		//copy of the env variables
	t_ast_node	*f_ast_node;	//First ast node
	char		*input;			//input introduces by the user
	char		**sub_tokens;	/*It contains the sub tokens 
								generated on the expansion*/
	int			i;				// Counter
	int			exp_f;			/*Flag to confirm there's something
								to expand (' , " , $). It let me know
								 if I have to resize the value of the token*/
	int			s_quot;			// flag to check if a char is ' outside of ""
	int			exit_status;
	int			redir_f;		/*Flag to count the number of the redirections
								 during the ast construction*/
	char		quot;			/*to define what type of quote
								 is the current quote*/
}	t_ms;

// MAIN

/*driver function*/
int			main(int arg, char **argv, char **envp);
/*infinite loop for waiting input*/
void		main_loop(t_ms *ms);
/*It copies each env var in a char* inside a linked list*/
t_list		*copy_env_var(char **envp);
/*Initializates strcut t_ms*/
void		init_ms(t_ms *ms);

// LEXER

/*It split the input in tokens*/
int			lexer(t_ms *ms);
/*It tokenizes operators (<, >, <<, >>, |)*/
void		token_operator(t_ms *ms);
/*It tokenizes words*/
int			token_word(t_ms *ms, int j);
/*It tokenizes input redir (<, <<)*/
void		token_redir_in(t_ms *ms, int j);
/*AÑADIR A .h:It tokenizer output redir (>, >>)*/
void		token_redir_out(t_ms *ms, int j);

// SYNTAX CHECKER

/*AUTOMATA (DFA) to check if the syntax written by the user is correct*/
int			syntax_checker(t_ms *ms);
/*It checks the ongoing state to follow the corresponding transition function*/
int			syntax_checker2(t_token *aux_t, t_state *st);
/*Transition function from 0 to the next*/
int			transit_0(t_token *aux_t, t_state *st);
/*Transition function from 1 or 2 to the next*/
int			transit_1_2(t_token *aux_t, t_state *st);
/*Transition function from 3 or 4 to the next*/
int			transit_3_4(t_token *aux_t, t_state *st);
/*Function to check if the token is a redirection token*/
int			is_redir(t_token *token);

// EXPANDER

/*main function to expand variables*/
void		expander(t_ms *ms);
/*It joins the subtokens splitted*/
void		join_subtokens(t_ms *ms, t_token *aux_t);
/*It splits the token in sub_tokens if needed*/
void		split_sub_token(t_ms *ms, t_token *aux_t, int *count);
/*It checks if there's something to expand 
	and start the expansion if needed*/
void		start_expand(t_ms *ms, t_token *aux_t, int *count);
/*It tells if there's any quote or $*/
int			is_exp_token(char c);
/*It counts how many subtokens will be created 
	due to the expand (to allocate the memory correctly)*/
void		count_subtokens(t_ms *ms, t_token *aux_t, int *count);
/*Second part of count subtokens*/
void		count_subtokens2(t_ms *ms, t_token *aux_t, int *count);
/*It counts subtokens created by dolar sign*/
void		count_dolar_subtokens(t_ms *ms, t_token *aux_t, int *count, char c);
/*It checks if a given word matches an enviroment
	 variable to count it as subtoken*/
void		check_env_count(t_ms *ms, t_token *aux_t, int *count);
/*It split tokens inside simple quotes*/
void		split_squot_subt(t_ms *ms, t_token *aux_t, int *count);
/*It split tokens not contained inside $, simple of double quotes*/
void		split_norm_subt(t_ms *ms, t_token *aux_t, int *count);
/*It split tokens inside double quotes*/
void		split_dquot_subt(t_ms *ms, t_token *aux_t, int *count);
/*It split tokens after dolar sign*/
void		split_dolar_subt(t_ms *ms, t_token *aux_t, int *count, char c);
/*Second par of split_dquot_subt*/
void		split_dquot_subt2(t_ms *ms, t_token *aux_t, int *count);
/*It checks if a given word matches an enviroment
	 variable to split it as subtoken*/
void		check_env_split(t_ms *ms, t_token *aux_t, int *count);
/*Second part of check_env_split*/
void		check_env_split2(t_ms *ms, int *count, char *word);
/*It replaes env variable by its value*/
char		*replace_env(t_ms *ms, t_list *tmp, char **word);

//AST

/*Driver function for creating the abstract syntax tree*/
t_ast_node	*ast_main(t_ms *ms, t_token *token);
/*It creates a pipe node*/
t_ast_node	*ast_pipe(t_ms *ms, t_token *token);
/*It creates a redirection node*/
t_ast_node	*ast_redirection(t_ms *ms, t_token *token);
/*It creates a file node*/
t_ast_node	*ast_file(t_ms *ms, t_token *token);
/*It creates a command node*/
t_ast_node	*ast_cmd(t_ms *ms, t_token *token);
/*It creates and alloc memory for a new node*/
t_ast_node	*new_ast_node(t_token_type type, t_ms *ms);
/*It counts how many arguments has a command node*/
int			argument_counter(t_token *token);

// EXECUTE
 
// BS_UTILS
int	ft_strcmp(const char *s1, const char *s2); //strcmp por si acaso
int update_env_var(char *var, t_list **my_env); //actualiza las variables de env(pensada para export)
int update_pwd_env(const char *old_dir); //actualiza las variables PWD y OLDPWD
void print_env(t_list **my_env); //imprie las variables con diferente formato segun si tienen o no valor

// BUILTINS
int builtin_echo(char **args, t_ms *ms); //muestra por pantalla el argc de forma diferente segun la flag
int valid_flag(char *str); //comprueba si la flag es valida
void print_arg(char *arg); //imprime el arg (funcion dividida)
int builtin_cd(char **args, t_ms *ms); //permite ir a un directorio especifico o el moverse entre ellos segun las flags
int special_case(char *str); //maneja casos especiales de cd (~ y --)
int builtin_pwd(char **args, t_ms *ms); //muestra por pantalla la ruta actual
int control_nums(char *str); //mismo que ft_isdigit pero maneja + y - 
int builtin_exit(char **args, t_ms *ms); //salida del programa, retornando diferentes códigos
int builtin_env(char **args, t_list *my_env, t_ms *ms); //imprime las variables de entorno
int is_correct(char *arg); //comprueba si la nomenclatura de la var de env es correcta
int add_to_env(char *var, t_list **my_env); //añade una var-env a través de nodos a la lista
int env_exportable(char *var, t_list **my_env); //maneja el caso de una var-env sin valor
int builtin_export(char **args, t_list **my_env, t_ms *ms); //imprime var-envs, crea y añade según la petición del usuario
int remove_env(char *var, t_list **my_env); //elimina var-envs, para el comando unset
int builtin_unset(char **args, t_list **my_env, t_ms *ms); //elimina var-envs
int handle_cd_home(t_ms *ms); //maneja cd sin argumentos (HOME)
int handle_cd_oldpwd(t_ms *ms); //maneja cd - (OLDPWD)
int handle_cd_path(char *path, t_ms *ms); //maneja cd con ruta específica
int is_builtin(char *cmd); //comprueba si es un builtin de otros comandos
int execute_builtin(char **args, t_ms *ms); //ejecuta los builtins segun el argc entrante

// EXECUTE_PID
int	execute_external_command(t_ast_node **args, t_ms **ms);


// FREE

/*It frees the linked list of env vars*/
void		free_env_list(t_list *my_env);
/*It frees the linked list of the tokens*/
void		free_token_list(t_token *tokens);
/*It frees the struct ms*/
void		free_ms(t_ms *ms);
/*It frees the subtokens splitted*/
void		free_subtokens(char **sub_tokens);
/*It frees the abstract syntax tree*/
void		free_ast(t_ast_node *ast);

// UTILS

/*It creates a new token node and fills it*/
t_token		*lstnew_token(char *value, t_token_type type);
/*It add a token to the back of the list*/
void		lstadd_back_token(t_token **tokens, t_token *new);
/*It fills the values of the token node and add it at the end of the list*/
void		fill_and_add_token_node(t_ms *ms, t_token_type type, int j);
/*It checks if the char is a redirection or a pipe, and return 1 in that case*/
int			is_operator(t_ms *ms);
/*It checks if the char is not allowed, and return 1 in that case*/
int			is_not_allowed(t_ms *ms);

/*Para imprimir y chequear los tokens (HAY QUE BORRARLA LUEGO)*/
void		print_tokens(t_ms *ms);

#endif