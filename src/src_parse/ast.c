
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

void	add_back_ast_node(t_ast_node **ast, t_ast_node *new)
{
	t_token	*curr;

	if (*tokens == NULL)
		*tokens = new;
	else
	{
		curr = *tokens;
		while (curr -> next != NULL)
			curr = curr ->next;
		curr -> next = new;
	}
}
t_ast_node	*ast_redirection(t_token *token)
{

}

t_ast_node	*ast_pipe(t_ms *ms)
{
	t_token		*tmp;
	t_token		*aux;
	t_ast_node	*new_node;
	t_token		*next;

	tmp = ms->tokens;
	aux = tmp;
	while (tmp && tmp->next)
	{
		//next = tmp->next;
		if (tmp->next->type == TOKEN_PIPE)
		{
			new_node = new_ast_node(tmp->next->type, ms);
			next = tmp->next->next;
			free(tmp-next->value);
			free(tmp->next);
			tmp->next = NULL;
			new_node->left = ast_redirection(ms->tokens);
			new_node->right = ast_pipe(next);
			return (new_node);
		}
		tmp = tmp->next; 
	}
}
