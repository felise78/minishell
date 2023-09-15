/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:19:58 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 18:53:20 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_general *all, t_token **cmdline, int i, t_builtins type)
{
	t_token		*cmd;
	int			ret;

	if (!cmdline)
		return (-1);
	cmd = locate_cmd(cmdline);
	if (!cmd)
		return (1);
	ret = 0;
	if (type == b_echo)
		ret = ft_echo(all->all_cmds[i].cmd_args);
	else if (type == b_env)
		ret = ft_env(all, all->all_cmds[i].cmd_args);
	else if (type == b_pwd)
		ret = ft_pwd(all->all_cmds[i].cmd_args);
	else if (type == b_cd)
		ret = ft_cd(all, all->all_cmds[i].cmd_args);
	else if (type == b_export)
		ret = ft_export(all, all->all_cmds[i].cmd_args);
	else if (type == b_unset)
		ret = ft_unset(all, all->all_cmds[i].cmd_args);
	else if (type == b_exit)
		ret = ft_exit(all, all->all_cmds[i].cmd_args);
	return (ret);
}

static int	exec_cmd(t_general *all, int i)
{
	char	**exec;
	int		ret;

	exec = all->all_cmds[i].cmd_args;
	ret = 0;
	if (all && check_absolute_path(all, i))
	{
		ret = find_path(all, i);
		if (ret != 0)
			exit_in_child(all, g_status);
	}
	if (execve(exec[0], exec, NULL) == -1)
		exit_in_child(all, -1);
	return (0);
}

int	ft_exec(t_general *all, t_token **cmdline, int i)
{
	t_builtins	cmd_type;
	t_token		cmd;
	int			ret;

	cmd.value = all->all_cmds[i].cmd_args[0];
	if (!(cmd.value))
		return (1);
	ret = 0;
	cmd.type = CMD;
	cmd_type = is_builtin(&cmd);
	ret = ft_set_redirection(&(all->all_cmds[i]));
	if (ret != 0)
		return (ret);
	ret = close_other_heredocs(all, i);
	if (ret != 0)
		return (ret);
	if (cmd_type != b_other)
		ret = exec_builtin(all, cmdline, i, cmd_type);
	else
		ret = exec_cmd(all, i);
	return (ret);
}
