/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:44:58 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/19 18:45:35 by pichatte         ###   ########.fr       */
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
	else if (((access(cmd, F_OK) == 0)
			&& access(cmd, X_OK) != 0) && ft_strchr(cmd, '/'))
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
