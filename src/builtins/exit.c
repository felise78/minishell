/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:27:55 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/19 12:28:46 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_all_digits(char *arg)
{
	int	i;

	if (!arg)
		return (-1);
	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_dprintf(2, "%s: numeric argument required\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_general *all, char **cmd_and_args)
{
	int	size;
	int	code;

	size = find_array_size(cmd_and_args);
	if (size <= 0)
		return (-1);
	code = 0;
	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
		ft_dprintf(STDOUT_FILENO, "exit\n");
	if (size > 1)
	{
		if (ft_all_digits(cmd_and_args[1]))
		{
			code = (unsigned char)ft_atoi(cmd_and_args[1]);
			if (size > 2)
			{
				ft_dprintf(2, "exit: too many arguments\n");
				return (1);
			}
		}
		else
			code = 2;
	}
	free_all(all);
	exit(code);
	return (0);
}
