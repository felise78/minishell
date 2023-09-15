/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:43:18 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/12 19:30:05 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_list	*node_in_env(t_general *all, char *line)
{
	t_list	*node;
	int		len;

	len = 0;
	while (line[len] && line[len] != '=')
		len++;
	node = all->env[0];
	while (node)
	{
		if (!ft_strncmp(node->content, line, len))
			return (node);
		node = node->next;
	}
	return (node);
}
