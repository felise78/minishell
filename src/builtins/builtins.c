/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pia <pia@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:12:17 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/21 00:16:23 by pia              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	is_n(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 1;
	while (s[i] == 'n')
		i++;
	if (!s[i])
		return (1);
	else
		return (0);
}

int	ft_echo(char **str_and_opt, int i, int n)
{
	n = 0;
	if (!str_and_opt || ft_strncmp(str_and_opt[0], "echo", 5))
		return (0);
	i = 1;
	while (str_and_opt[i])
	{
		if (i == 1)
		{	
			while (str_and_opt[i]
				&& !ft_strncmp(str_and_opt[i], "-n", 2) && is_n(str_and_opt[i]))
			{
				n = 1;
				i++;
			}
		}
		if (str_and_opt[i] && str_and_opt[i + 1])
			ft_dprintf(1, "%s ", str_and_opt[i]);
		else if (str_and_opt[i] && !str_and_opt[i + 1])
			ft_dprintf(1, "%s", str_and_opt[i]);
		if (str_and_opt[i])
			i++;
	}
	if (!n)
		ft_dprintf(1, "\n");
	return (0);
}

int	ft_pwd(char **cmd_and_args)
{
	char	*pwd;

	if (!cmd_and_args || ft_strncmp(cmd_and_args[0], "pwd", 4))
		return (-1);
	if (cmd_and_args[1] && cmd_and_args[1][0] == '-')
	{
		ft_dprintf(2, "error: %s: no options permitted\n", cmd_and_args[1]);
		return (g_status = 2, 2);
	}
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}

static int	is_exit(t_general *all)
{
	if (!all || !all->all_cmds)
		return (0);
	if (!ft_strncmp(all->all_cmds[0].cmd_args[0], "exit", 5))
		return (1);
	return (0);
}

int	dup_fds_for_builtin(t_general *all, t_token **cmdline)
{
	int	tmp_in;
	int	tmp_out;
	int	ret;

	if (is_exit(all))
		return (ft_exec(all, cmdline, 0));
	tmp_in = dup(STDIN_FILENO);
	if (tmp_in == -1)
		return (perror("tmp_in"), g_status = 1, 1);
	tmp_out = dup(STDOUT_FILENO);
	if (tmp_out == -1)
	{
		close(tmp_in);
		return (perror("tmp_out"), g_status = 1, 1);
	}
	ret = ft_exec(all, cmdline, 0);
	if (dup2(tmp_in, STDIN_FILENO) == -1)
		return (perror("tmp_in"), g_status = 1, 1);
	if (dup2(tmp_out, STDOUT_FILENO) == -1)
		return (perror("tmp_out"), g_status = 1, 1);
	if (close(tmp_in) == -1)
		return (perror("tmp_in"), g_status = 1, 1);
	if (close(tmp_out) == -1)
		return (perror("tmp_out"), g_status = 1, 1);
	return (ret);
}
