/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:07:28 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 15:26:18 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	g_status = 1;

void	warning_eof(char *delim)
{
	ft_putstr_fd("minishell : warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}

void	handler_heredoc(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	g_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	heredoc_count(t_token *current)
{
	int	i;

	i = 0;
	while (current)
	{
		if (current->type == HEREDOC)
			i++;
		else if (current->type == PIPE)
			return (i);
		current = current->next;
	}
	return (i);
}
