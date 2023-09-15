/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:16:26 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 17:04:21 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_heredoc(t_token **here_node)
{
	t_token	*tmp;

	tmp = *here_node;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp && tmp->next && tmp->next->type == HEREDOC)
			return (0);
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

int	close_other_heredocs(t_general *all, int i)
{
	int	j;
	
	if (!all || !all->all_cmds)
		return (0);
	j = 0;
	while (j <= all->pipeline->pipes)
	{
		if (j != i)
		{
			if (all->all_cmds[j].here_fd[0] != -1)
			{
				if (close(all->all_cmds[j].here_fd[0]) == -1)
					return (perror("here_fd[0]"), 1);
			}
		}
		j++;
	}
	return (0);
}