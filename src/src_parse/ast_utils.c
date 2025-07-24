
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

int	argument_counter(t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
			tmp = tmp->next;
		else
			count++;
		tmp = tmp->next;
	}
	return (count);
}
