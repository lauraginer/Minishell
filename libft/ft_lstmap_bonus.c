/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:10:31 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/19 15:25:35 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res_lst;
	t_list	*aux;

	res_lst = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		aux = ft_lstnew(f(lst -> content));
		if (!aux)
		{
			ft_lstclear(&res_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&res_lst, aux);
		lst = lst -> next;
	}
	return (res_lst);
}
