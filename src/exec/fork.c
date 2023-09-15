/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:09:42 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 18:54:13 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_general *all)
{
	int	status;
	int	i;
	int	ret;

	i = 0;
	while (i <= all->pipeline->pipes)
	{
		ret = waitpid(all->pipeline->pid[i], &status, 0);
		if (ret == -1 && i == all->pipeline->pipes)
			return ;
		i++;
	}
	if (WIFEXITED(status) && i == all->pipeline->pipes + 1)
		g_status = WEXITSTATUS(status);
}

int	fork_single_command(t_general *all, t_token **cmdline)
{
	int				ret;
	__sighandler_t	old_signal[2];	

	ret = 0;
	old_signal[0] = signal(SIGINT, child_handler);
	old_signal[1] = signal(SIGQUIT, child_handler);
	all->pipeline->pid[0] = fork();
	if (all->pipeline->pid[0] == -1)
		return (1);
	if (all->pipeline->pid[0] == 0)
	{
		ret = ft_exec(all, cmdline, 0);
		exit_in_child(all, g_status);
	}
	else
	{
		if (check_and_close_heredoc(all, 0) != 0)
			return (1);
		ft_wait(all);
	}
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	return (g_status);
}

static int	ft_fork_pipes(t_general *all, t_token **cmdline)
{
	__sighandler_t	old_signal[2];

	old_signal[0] = signal(SIGINT, child_handler);
	old_signal[1] = signal(SIGQUIT, child_handler);
	g_status = exec_pipes(all, cmdline);
	if (g_status != 0)
		return (g_status);
	ft_wait(all);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	if (close(all->pipeline->prev_pipe) == -1)
		g_status = 1;
	return (g_status);
}

int	ft_fork(t_general *all, t_token **cmdline)
{
	t_token			*new;
	t_token			*cmd;
	int				ret;
	
	new = *cmdline;
	ret = 0;
	g_status = parse_cmdline(all, &new);
	if (g_status != 0)
		return (g_status);
	cmd = locate_cmd(cmdline);
	if (!cmd)
		return (g_status);
	if (all->pipeline->pipes)
		ret = ft_fork_pipes(all, cmdline);
	// else if (cmdline && cmdline[0] && cmdline[0]->type == VAR)
	// 	return (0);
	else if (cmd && !is_builtin(cmd))
		ret = fork_single_command(all, cmdline);
	else
		ret = ft_exec(all, cmdline, 0);
	return (g_status);
}
