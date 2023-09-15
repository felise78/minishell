/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:56:08 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 15:32:33 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_redirection(t_command *cmd)
{
	t_token	*tmp;
	int		fd;

	if (!cmd->redirections)
		return (0);
	tmp = cmd->redirections;
	while (tmp)
	{
		if (open_fd(cmd, &tmp, &fd) != 0)
			return (close(fd), 1);
		if (fd == -1)
		{
			perror(tmp->value);
			return (1);
		}
		if (ft_dup_redir(&tmp, &fd) != 0)
			return (close(fd), 1);
		if (close(fd) == -1)
		{
			perror("close");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	open_fd(t_command *cmd, t_token **tmp, int *fd)
{
	if (!tmp || !(*tmp))
		return (0);
	if ((*tmp)->type == REDIR_INPUT)
		*fd = open((*tmp)->value, O_RDONLY);
	else if ((*tmp)->type == REDIR_OUTPUT)
		*fd = open((*tmp)->value, O_WRONLY | O_TRUNC | O_CREAT, 00666);
	else if ((*tmp)->type == APPEND)
		*fd = open((*tmp)->value, O_WRONLY | O_APPEND | O_CREAT, 00666);
	else
	{
		*fd = dup(cmd->here_fd[0]);
		if (close(cmd->here_fd[0]) == -1)
			return (perror("here_fd[0]"), 1);
	}
	return (0);
}

int	ft_dup_redir(t_token **tmp, int *fd)
{
	if (!tmp || !(*tmp))
		return (0);
	if ((*tmp)->type == REDIR_INPUT || (*tmp)->type == HEREDOC)
	{
		if (dup2(*fd, STDIN_FILENO) == -1)
		{
			perror((*tmp)->value);
			return (1);
		}
	}
	if ((*tmp)->type == REDIR_OUTPUT || (*tmp)->type == APPEND)
	{
		if (dup2(*fd, STDOUT_FILENO) == -1)
		{
			perror((*tmp)->value);
			return (1);
		}
	}
	return (0);
}

int	set_redir_lists(t_token **add_to, t_token *new_node)
{
	if (!add_to || !new_node)
		return (1);
	if (!(*add_to))
		*add_to = new_node;
	else
		ft_token_add_back(add_to, new_node);
	return (0);
}
