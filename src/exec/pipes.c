/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:20:48 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 14:31:13 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_child(t_general *all, int i, t_token **cmdline);

int	ft_parent(t_pipe *pipeline, int i)
{
	if (close(pipeline->fd[1]) == -1)
		return (perror_return("fd[1]", 1));
	if (pipeline->prev_pipe != -1)
	{
		if (close(pipeline->prev_pipe) == -1)
			return (perror_return("prev_pipe", 1));
	}
	pipeline->prev_pipe = dup(pipeline->fd[0]);
	if (pipeline->prev_pipe == -1)
		return (perror_return("fd[0]", 1));
	if (close(pipeline->fd[0]) == -1)
		return (perror_return("fd[0]", 1));
	if (check_and_close_heredoc(pipeline->all, i) != 0)
		return (1);
	return (0);
}

int	ft_dup(t_pipe *pipeline, int cmd_index)
{
	if (cmd_index != 0)
	{
		if (cmd_index == pipeline->pipes)
		{	
			if (close(pipeline->fd[0]) == -1)
				return (perror_return("fd[0]", 1));
			if (close(pipeline->fd[1]) == -1)
				return (perror_return("fd[1]", 1));
		}
		if (dup2(pipeline->prev_pipe, STDIN_FILENO) == -1)
			return (perror_return("prev_pipe", 1));
		if (close(pipeline->prev_pipe) == -1)
			return (perror_return("prev_pipe", 1));
	}
	if (cmd_index != pipeline->pipes)
	{
		if (close(pipeline->fd[0]) == -1)
			return (perror_return("fd[0]", 1));
		if (dup2(pipeline->fd[1], STDOUT_FILENO) == -1)
			return (perror("fd[1]"), 1);
		if (close(pipeline->fd[1]) == -1)
			return (perror("fd[1]"), 1);
	}
	return (0);
}

int	pipe_count(t_token **cmd_line)
{
	int		counter;
	t_token	*tmp;

	counter = 0;
	tmp = *cmd_line;
	while (tmp)
	{
		if (tmp->type == PIPE)
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

int	exec_pipes(t_general *all, t_token **cmdline)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i <= all->pipeline->pipes)
	{
		if (pipe(all->pipeline->fd) == -1)
			return (perror_return("pipe", 1));
		all->pipeline->pid[i] = fork();
		if (all->pipeline->pid[i] == -1)
			return (perror_return("fork", 1));
		if (all->pipeline->pid[i] == 0)
			ft_exec_child(all, i, cmdline);
		else
		{
			ret = ft_parent(all->pipeline, i);
			if (ret != 0)
				return (ret);
		}
		i++;
	}
	return (0);
}

static int	ft_exec_child(t_general *all, int i, t_token **cmdline)
{
	int		ret;

	ret = ft_dup(all->pipeline, i);
	if (ret != 0)
		exit_in_child(all, ret);
	ret = ft_exec(all, cmdline, i);
	exit_in_child(all, ret);
	return (ret);
}
