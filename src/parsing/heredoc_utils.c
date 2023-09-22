/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:07:28 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/22 17:14:08 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		close_heredoc_fd(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			perror("fd");
			g_status = 2;
			return (0);
		}
	}
	return (1);
}

void handler_no_nl(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	warning_eof(char *delim)
{
	ft_putstr_fd("minishell : warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
	signal(SIGINT, &handler_no_nl);
}

void	handler_heredoc(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	g_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	signal(SIGINT, &handler_no_nl);
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
