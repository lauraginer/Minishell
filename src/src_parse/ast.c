
#include "../../inc/minishell.h"


t_ast_node	*new_ast_node(t_token_type type, t_ms *ms)
{
	t_ast_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast_node));
	if (!new_node)
		free_ms(ms);
	new_node->type = type;
	return (new_node);
}

t_ast_node	*ast_cmd(t_ms *ms, t_token *token)
{
	
}

t_ast_node	*ast_file(t_ms *ms, t_token *token)
{
	t_ast_node	*new_node;
	int			i;

	i = 0;
	new_node = new_ast_node(TOKEN_WORD, ms);
	new_node->args = malloc(sizeof(char*) * 2);
	if (!new_node->args)
		free_ms(ms);
	new_node->args[0] = token->value; // cuidado al liberar el ast, creo que lo libero tambien en tokens
	new_node->args[1] = NULL;
	return (new_node);
}

t_ast_node	*ast_redirection(t_ms *ms, t_token *token)
{
	t_token		*tmp;
	t_ast_node	*new_node;
	int			redir_cnt;

	ms->redir_f++;
	redir_cnt = 0;
	tmp = token;
	while (tmp)
	{
		if (is_redir(tmp))
		{
			redir_cnt++;
			if (redir_cnt == ms->redir_f)
			{
				new_node = new_ast_node(tmp->type, ms);
				new_node->left = ast_redirection(ms, token);
				new_node->right = ast_file(ms, tmp->next);
				return (new_node);
			}
		}
		tmp = tmp->next;
	}
	return (ast_cmd(ms, token));
}

t_ast_node	*ast_pipe(t_ms *ms, t_token *token)
{
	t_token		*tmp;
	t_ast_node	*new_node;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			new_node = new_ast_node(tmp->type, ms);
			new_node->left = ast_redirection(ms, token);
			ms->redir_f = 0;
			new_node->right = ast_pipe(ms, tmp->next);
			return(new_node);
		}
		token = token->next;
	}
	return (ast_redirection(ms, token));
}
