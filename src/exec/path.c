/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pia <pia@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:41:22 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/21 00:03:56 by pia              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path(t_general *all, int i)
{
	char	*path_in_env;
	char	**directories;

	path_in_env = ft_getenv(all, "PATH");
	if (!path_in_env)
		path_in_env = "";
	directories = ft_split(path_in_env, ':');
	if (!directories)
		return (g_status = -2, 1);
	return (join_to_path(all, i, directories));
}

int	cmd_exists(t_general *all, int i, char **directories, char *slash)
{
	free(all->all_cmds[i].cmd_args[0]);
	all->all_cmds[i].cmd_args[0] = ft_strdup(slash);
	free_tab(&directories);
	free(slash);
	if (!all->all_cmds[i].cmd_args[0])
		return (g_status = -2, 1);
	return (0);
}

int	join_to_path(t_general *all, int i, char **directories)
{
	char	*slash;
	int		j;

	j = 0;
	while (directories && directories[j])
	{
		if (join_to_path_2(all->all_cmds[i].cmd_args[0],
				&slash, directories, j) != 0)
			return (1);
		if (access(slash, F_OK | X_OK) == 0 && !ft_isdir(slash))
			return (cmd_exists(all, i, directories, slash));
		free(slash);
		j++;
	}
	if (directories && !directories[0])
		perror(all->all_cmds[i].cmd_args[0]);
	else
		ft_dprintf(2, "'%s': command not found\n", all->all_cmds[i].cmd_args[0]);
	free_tab(&directories);
	return (g_status = 127, 127);
}

int	join_to_path_2(char *cmd, char **slash, char **directories, int j)
{
	*slash = ft_strjoin(directories[j], "/");
	if (!*slash)
	{
		perror(directories[j]);
		free_tab(&directories);
		g_status = -2;
		return (1);
	}
	*slash = ft_strjoin_free(*slash, cmd, 1);
	if (!*slash)
	{
		perror(cmd);
		free(*slash);
		free_tab(&directories);
		g_status = -2;
		return (1);
	}
	return (0);
}
