/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:02:00 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 18:47:44 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isdir(char *pathname)
{
	struct stat statbuf;

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

int	del_periods(t_list **path, char **dir)
{
	t_list	*tmp;
	t_list	*new_tmp;

	tmp = *path;
	while (tmp)
	{
		if (!ft_strncmp("..", tmp->content, 3))
		{
			new_tmp = tmp->next;
			ft_lstdelone(path, tmp->previous, &use_free);
			ft_lstdelone(path, tmp, &use_free);
			tmp = new_tmp;
		}
		else if (!ft_strncmp(".", tmp->content, 2))
		{
			new_tmp = tmp->next;
			ft_lstdelone(path, tmp, &use_free);
			tmp = new_tmp;
		}
		else
			tmp = tmp->next;
	}
	return (join_dir(path, dir));
}

int	check_periods(char **dir)
{
	char	**split_slash;
	t_list	*path;
	int		i;
	int		ret;

	split_slash = ft_split(*dir, '/');
	if (!split_slash)
		return (-1);
	ret = 0;
	path = NULL;
	i = 0;
	while (split_slash[i])
	{
		ft_lstadd_back(&path, ft_lstnew(split_slash[i]));
		i++;
	}
	ret = del_periods(&path, dir);
	ft_lstclear(&path, &free);
	free(split_slash);
	return (ret);
}
