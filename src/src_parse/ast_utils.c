/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:26:59 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/08/13 11:27:07 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
