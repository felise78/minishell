/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:15:07 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/15 12:26:42 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return (0);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
