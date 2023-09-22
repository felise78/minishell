/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:02:00 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/18 14:31:09 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isdir(char *pathname)
{
	struct stat	statbuf;

	if (stat(pathname, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
		return (1);
	else
		return (0);
}

int	join_dir(t_list **path, char **dir)
{
	t_list	*tmp;

	tmp = *path;
	free (*dir);
	*dir = ft_strjoin("/", tmp->content);
	if (!*dir)
		return (-1);
	tmp = tmp->next;
	while (tmp)
	{
		*dir = ft_strjoin_free(*dir, "/", 1);
		if (!dir)
			return (-2);
		*dir = ft_strjoin_free(*dir, tmp->content, 1);
		if (!*dir)
			return (-3);
		tmp = tmp->next;
	}
	return (0);
}
