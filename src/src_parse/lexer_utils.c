

#include "../../inc/minishell.h"

int	is_operator(t_parse *parse)
{
	if (parse->input[parse->i] == '<'
		|| parse->input[parse->i] == '>'
		|| parse->input[parse->i] == '|')
		return (1);
	return (0);
}

int	is_not_allowed(t_parse *parse)
{
	if (parse->input[parse->i] == '&'
		|| parse->input[parse->i] == ';'
		|| parse->input[parse->i] == '\\')
		return (1);
	return (0);
}

void	token_redir_in(t_list *my_env, t_parse *parse, int j)
{
	parse->i++;
	if (parse->input[parse->i] == '<')
	{
		parse->i++;
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_HEREDOC, j);
	}
	else
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_IN, j);
}

void	token_redir_out(t_list *my_env, t_parse *parse, int j)
{
	parse->i++;
	if (parse->input[parse->i] == '>')
	{
		parse->i++;
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_APPEND, j);
	}
	else
		fill_and_add_token_node(parse, my_env, TOKEN_REDIR_OUT, j);
}
