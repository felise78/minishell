/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:36:13 by pichatte          #+#    #+#             */
/*   Updated: 2022/12/06 15:36:14 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*add;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		add = ft_lstnew((*f)(lst->content));
		if (!add)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, add);
		lst = lst->next;
	}
	return (new);
}
