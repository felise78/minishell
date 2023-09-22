/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:23:43 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/19 18:56:00 by pichatte         ###   ########.fr       */
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
		if (size < 2)
			ft_dprintf(2, "cd: missing pathname\n");
		if (size > 2)
			ft_putstr_fd("cd: too many arguments\n", 2);
		g_status = 1;
		return (2);
	}
	return (0);
}

int	set_pwd(t_general *all, char *oldpwd)
{
	t_list	*old;
	t_list	*current;
	char	*pwd;

	old = node_in_env(all, "OLDPWD");
	current = node_in_env(all, "PWD");
	pwd = NULL;
	if (old)
	{
		free(old->content);
		old->content = ft_strjoin_free("OLDPWD=", oldpwd, 2);
		if (!old->content)
			return (g_status = -2, -2);
	}
	if (current)
	{
		free(current->content);
		pwd = getcwd(pwd, 0);
		if (!pwd)
			return (g_status = -2, -2);
		current->content = ft_strjoin_free("PWD=", pwd, 2);
		if (!current->content)
			return (g_status = -2, -2);
	}
	return (export_new_env(all));
}

int	cd_and_set_pwd(t_general *all, char *dir, char *original)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (!ft_isdir(dir))
	{
		if (original)
			ft_dprintf(2, "%s: Not a directory\n", original);
		return (1);
	}
	else if (access(dir, F_OK | X_OK) != 0)
		return (perror(original), 1);
	else
	{
		oldpwd = getcwd(oldpwd, 0);
		if (!oldpwd)
			return (g_status = -2, -2);
		if (chdir(dir))
			return (1);
	}
	set_pwd(all, oldpwd);
	return (0);
}

int	ft_cd(t_general *all, char **cmd_and_args)
{
	char	*pwd;

	if (cd_errors(cmd_and_args))
		return (1);
	pwd = NULL;
	if (cmd_and_args[1] && cmd_and_args[1][0] == '/')
	{	
		pwd = ft_strdup(cmd_and_args[1]);
		if (!pwd)
			return (g_status = -2, -2);
	}		
	else
	{
		pwd = getcwd(pwd, 0);
		if (!pwd)
			return (g_status = -2, -2);
		pwd = ft_strjoin_free(pwd, "/", 1);
		pwd = ft_strjoin_free(pwd, cmd_and_args[1], 1);
		if (!pwd)
			return (-2);
	}
	if (cd_and_set_pwd(all, pwd, cmd_and_args[1]))
		return (free(pwd), g_status = 1, 1);
	return (free(pwd), 0);
}
