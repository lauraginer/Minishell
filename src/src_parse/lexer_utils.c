

#include "../../inc/minishell.h"

int	is_operator(t_ms *ms)
{
	if (ms->input[ms->i] == '<'
		|| ms->input[ms->i] == '>'
		|| ms->input[ms->i] == '|')
		return (1);
	return (0);
}

int	is_not_allowed(t_ms *ms)
{
	if (ms->input[ms->i] == '&'
		|| ms->input[ms->i] == ';'
		|| ms->input[ms->i] == '\\')
		return (1);
	return (0);
}

void	token_redir_in(t_ms *ms, int j)
{
	ms->i++;
	if (ms->input[ms->i] == '<')
	{
		ms->i++;
		fill_and_add_token_node(ms, TOKEN_REDIR_HEREDOC, j);
	}
	else
		fill_and_add_token_node(ms, TOKEN_REDIR_IN, j);
}

void	token_redir_out(t_ms *ms, int j)
{
	ms->i++;
	if (ms->input[ms->i] == '>')
	{
		ms->i++;
		fill_and_add_token_node(ms, TOKEN_REDIR_APPEND, j);
	}
	else
		fill_and_add_token_node(ms, TOKEN_REDIR_OUT, j);
}
