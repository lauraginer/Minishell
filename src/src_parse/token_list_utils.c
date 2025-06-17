/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:54:18 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/06/17 18:09:34 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lstnew_token(char *value, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
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
