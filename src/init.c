/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:30:28 by bourdon           #+#    #+#             */
/*   Updated: 2023/09/13 18:14:02 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pointers(t_general *all, t_pipe *pipeline, t_token **cmd_line)
{
	all->pipeline = pipeline;
	pipeline->all = all;
	all->cmdline = cmd_line;
	pipeline->cmdline = all->cmdline;
}

int	ft_set_env(t_general *all, t_list **env, char **envp)
{
	int	ret;

	all->env = env;
	all->new_env = copy_tab(envp);
	if (!all->new_env)
		return (-2);
	ret = env_init(envp, env);
	if (ret != 0)
	{
		free_tab(&(all->new_env));
		return (ret);
	}
	return (0);
}

int	ft_init_pipes(t_general *all, t_token **cmd_line)
{
	int		nb_pipe;
	int		i;

	i = 0;
	nb_pipe = pipe_count(cmd_line);
	all->all_cmds = (t_command *)malloc(sizeof(t_command) * (nb_pipe + 1));
	if (!all->all_cmds)
		return (0);
	all->pipeline->pid = (pid_t *)malloc(sizeof(pid_t) * (nb_pipe + 1));
	if (!(all->pipeline->pid))
		return (0);
	while (i <= nb_pipe)
	{
		all->all_cmds[i].here_fd[0] = -1;
		all->all_cmds[i].here_fd[1] = -1;
		all->all_cmds[i].redirections = NULL;
		all->all_cmds[i].cmd_args = NULL;
		i++;
	}
	all->pipeline->prev_pipe = -1;
	all->pipeline->pipes = nb_pipe;
	return (1);
}
