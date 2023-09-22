/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:43:18 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/19 18:54:38 by pichatte         ###   ########.fr       */
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

int	sort_envp(t_general *all)
{
	t_list	*env_to_sort;
	t_list	*tmp;
	t_list	*min;

	if (!all->env || !all->env[0])
		return (0);
	env_to_sort = copy_list(all->env);
	if (!env_to_sort)
		return (g_status = -2, -2);
	while (env_to_sort)
	{
		tmp = env_to_sort;
		min = env_to_sort;
		while (tmp)
		{
			if (tmp && min
				&& ft_strncmp(min->content, tmp->content,
					ft_strlen(tmp->content) + 1) > 0)
				min = tmp;
			tmp = tmp->next;
		}
		ft_dprintf(1, "export %s\n", (char *)min->content);
		ft_lstdelone(&env_to_sort, min, &use_free);
	}
	return (0);
}
