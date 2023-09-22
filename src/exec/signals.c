/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:54:39 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/22 18:24:33 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{		
	if (signum == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	handle_eof(t_general *all)
{
	char	*exit[2];

	exit[0] = "exit";
	exit[1] = NULL;
	g_status = ft_exit(all, exit);
	return (g_status);
}

void	child_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		printf("\n");
	}
	if (signum == SIGQUIT)
	{
		g_status = 131;
		printf("Quit (core dumped)\n");
	}
}

void	ft_signals_child(void)
{
	struct sigaction	child;

	child.sa_handler = &child_handler;
	sigemptyset(&child.sa_mask);
	child.sa_flags = 0;
	if (sigaction(SIGINT, &child, NULL) == -1)
	{
		perror("sigaction");
		return ;
	}
	if (sigaction(SIGQUIT, &child, NULL) == -1)
	{
		perror("sigaction");
		return ;
	}
}

void	ft_signals_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return ;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
