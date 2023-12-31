/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:42:45 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/21 17:19:02 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_set_null(t_general *all)
{
	ft_free_cmd_line(all->cmdline);
	free_cmds(all);
	free(all->pipeline->pid);
	all->pipeline->pid = NULL;
}

void	ft_free_cmd_line(t_token **cmd_line)
{
	t_token	*current;
	t_token	*temp;

	if (!cmd_line)
		return ;
	current = *cmd_line;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
	(*cmd_line) = NULL;
	cmd_line = NULL;
}

void	free_cmds(t_general *all)
{
	int	i;

	if (!all)
		return ;
	i = 0;
	if (all->fd_tmp != -1)
		close_heredoc_fd(all->fd_tmp); // a proteger ?
	all->fd_tmp = -1; //
	while (i <= all->pipeline->pipes)
	{
		if (all->all_cmds)
		{
			if(all->all_cmds[i].here_fd[0] != -1)
				close_heredoc_fd(all->all_cmds[i].here_fd[0]); // a proteger ? 
			if(all->all_cmds[i].here_fd[1] != -1)
				close_heredoc_fd(all->all_cmds[i].here_fd[1]); // a proteger ? 
			free_tab(&(all->all_cmds[i].cmd_args));
			ft_free_cmd_line(&(all->all_cmds[i].redirections));
		}
		i++;
	}
	if (all->all_cmds)
		free(all->all_cmds);
	all->all_cmds = NULL;
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!tab || !(*tab))
		return ;
	while ((*tab) && (*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	if (*tab)
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
	}
	free(*tab);
	(*tab) = NULL;
}

void	free_all(t_general *all)
{
	rl_clear_history();
	ft_lstclear(all->env, &use_free);
	free_tab(&(all->new_env));
	ft_free_cmd_line(all->cmdline);
	free_cmds(all);
	free(all->pipeline->pid);
	all->pipeline->pid = NULL;
}
