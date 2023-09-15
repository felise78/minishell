/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:41:22 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 18:49:53 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	abs_path_errors(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0 && ft_isdir(cmd))
	{
		ft_dprintf(2, "%s: is a directory\n", cmd);
		return (126);
	}
	else if ((access(cmd, F_OK) != 0) && ft_strchr(cmd, '/'))
		return (perror(cmd), 127);
	else if (((access(cmd, F_OK) == 0) && access(cmd, X_OK) != 0) && ft_strchr(cmd, '/'))
		return (perror(cmd), 126);
	else
		return (0);
}

int	check_absolute_path(t_general *all, int i)
{
	char	*cmd;
	int		code;

	if (!all | !(all->all_cmds))
		return (-1);
	cmd = all->all_cmds[i].cmd_args[0];
	if (!cmd)
		return (1);
	code = abs_path_errors(cmd);
	if (code != 0)
	{
		free_all(all);
		exit(code);
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	else
		return (1);
}

int	find_path(t_general *all, int i)
{
	char	*path_in_env;
	char	**directories;

	path_in_env = ft_getenv(all, "PATH");
	if (!path_in_env && (!all->env || !(all->env[0])))
	{
		path_in_env = "/usr/local/sbin:/usr/local/bin:\
			/usr/sbin:/usr/bin:/sbin:/bin:\
			/usr/games:/usr/local/games:/snap/bin";
	}
	else if (!path_in_env && (all->env && all->env[0]))
		return (-1);
	else
	{
	}
	directories = ft_split(path_in_env, ':');
	if (!directories)
		return (g_status = -2, 1);
	return (join_to_path(all, i, directories));
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
		{
			free(all->all_cmds[i].cmd_args[0]);
			all->all_cmds[i].cmd_args[0] = ft_strdup(slash);
			free_tab(&directories);
			free(slash);
			if (!all->all_cmds[i].cmd_args[0])
				return (g_status = -2, 1);
			return (0);
		}
		free(slash);
		j++;
	}
	free_tab(&directories);
	ft_dprintf(2, "'%s': command not found\n", all->all_cmds[i].cmd_args[0]);
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
