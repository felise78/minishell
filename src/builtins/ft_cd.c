/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:23:43 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 18:00:27 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd_errors(char **cmd_and_args)
{
	int	size;

	if (!cmd_and_args || ft_strncmp(cmd_and_args[0], "cd", 3))
		return (1);
	size = find_array_size(cmd_and_args);
	if (size != 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (2);
	}
	return (0);
}

int	set_pwd(t_general *all, char *new_pwd)
{
	t_list	*tmp;
	t_list	*old;
	t_list	*current;

	old = NULL;
	current = NULL;
	tmp = all->env[0];
	old = node_in_env(all, "OLDPWD");
	current = node_in_env(all, "PWD");
	if (!old || !current)
		return (1);
	new_pwd = ft_strjoin_free("PWD=", new_pwd, 2);
	if (!new_pwd)
		return (-2);
	current->content = (char *)(ft_strjoin_free("OLD", current->content, 2));
	if (!current->content)
		return (-2);
	free(old->content);
	old->content = current->content;
	current->content = (char *)new_pwd;
	return (0);
}

int	cd_and_set_pwd(t_general *all, char *dir)
{
	if (access(dir, F_OK | X_OK) != 0)
		return (1);
	else
	{
		check_periods(&dir);
		if (chdir(dir))
			return (1);
	}
	set_pwd(all, dir);
	return (0);
}

int	ft_cd(t_general *all, char **cmd_and_args)
{
	char	*pwd;

	if (cd_errors(cmd_and_args))
		return (1);
	pwd = NULL;
	if (ft_strchr(cmd_and_args[1], '/') == cmd_and_args[1])
	{	
		pwd = ft_strdup(cmd_and_args[1]);
		if (!pwd)
			return (-2);
	}		
	else
	{
		pwd = ft_strjoin_free(getcwd(pwd, 0), "/", 1);
		pwd = ft_strjoin_free(pwd, cmd_and_args[1], 1);
		if (!pwd)
			return (-2);
	}
	if (cd_and_set_pwd(all, pwd))
	{
		perror(cmd_and_args[1]);
		free(pwd);
		return (1);
	}
	return (0);
}
