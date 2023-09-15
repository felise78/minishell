/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:12:17 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 10:56:22 by pichatte         ###   ########.fr       */
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

int	ft_echo(char **str_and_opt)
{
	int	size;
	int	i;
	int	n;

	n = 0;
	if (!str_and_opt || ft_strncmp(str_and_opt[0], "echo", 5))
		return (-1);
	size = find_array_size(str_and_opt);
	if (size > 1 && !ft_strncmp(str_and_opt[1], "-n", 2)
		&& is_n(str_and_opt[1]))
		n = 1;
	i = n + 1;
	while (str_and_opt[i])
	{
		if (str_and_opt[i + 1])
			ft_dprintf(1, "%s ", str_and_opt[i]);
		else
			ft_dprintf(1, "%s", str_and_opt[i]);
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
		return (2);
	}
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
