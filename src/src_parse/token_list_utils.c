

#include "../../inc/minishell.h"

t_token	*lstnew_token(char *value, t_token_type type)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	return (new_node);
}

void	lstadd_back_token(t_token **tokens, t_token *new)
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

void	fill_and_add_token_node(t_ms *ms, t_token_type type, int j)
{
	t_token	*node;
	char	*value;

	value = ft_substr(ms->input, j, ms->i - j);
	if (!value)
		free_ms(ms);
	node = lstnew_token(value, type);
	if (!node)
	{
		free(value);
		free_ms(ms);
	}
	lstadd_back_token(&(ms->tokens), node);
}
