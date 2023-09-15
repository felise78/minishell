/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:26:24 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 14:34:56 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_in_child(t_general *all, int code)
{
	free_all(all);
	g_status = code;
	exit(code);
}

int	perror_return(char *message, int code)
{
	perror(message);
	return (code);
}

int	check_and_close_heredoc(t_general *all, int i)
{
	if (!all || !all->all_cmds)
		return (0);
	if (all->all_cmds[i].here_fd[0] != -1)
	{
		if (close(all->all_cmds[i].here_fd[0]) == -1)
		{
			perror("here_fd[0]");
			return (1);
		}
		all->all_cmds[i].here_fd[0] = -1;
	}
	return (0);
}