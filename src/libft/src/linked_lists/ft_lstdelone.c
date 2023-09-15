/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:01:29 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/01 18:04:41 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst, t_list *node, void (*del)(void *))
{
	if (!lst || !node)
		return ;
	if (node == (*lst))
	{
		*lst = (*lst)->next;
		if (*lst)
			(*lst)->previous = NULL;
	}
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;
	if (del)
	{
		(*del)(node->content);
		node->content = NULL;
	}
	free(node);
	node = NULL;
}
