/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:28:46 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/15 12:22:02 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	// free(new_list); ///
	// new_list = NULL; ///
	if (!new_list)
		return (0);
	new_list->content = content;
	new_list->next = NULL;
	new_list->previous = NULL;
	return (new_list);
}
