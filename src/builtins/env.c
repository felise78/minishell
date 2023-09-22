/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:51:26 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/15 12:36:36 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_general *all, char **cmd_and_args)
{
	int	i;

	if (!cmd_and_args || ft_strncmp(cmd_and_args[0], "env", 4))
		return (1);
	if (find_array_size(cmd_and_args) > 1)
		return (ft_dprintf(2, "env: this command takes no arguments\n"), 1);
	i = 0;
	while (all->new_env && (all->new_env)[i])
	{
		if (ft_strchr((all->new_env)[i], '='))
			ft_dprintf(1, "%s\n", (all->new_env)[i]);
		i++;
	}
	return (0);
}

int	env_init(char **envp, t_list **env)
{
	int		i;

	if (!env)
		return (-1);
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(envp[i])));
		if (!ft_lstlast(env) || !(ft_lstlast(env)->content))
		{
			ft_lstclear(env, &free);
			return (-2);
		}
		i++;
	}
	return (0);
}

char	*ft_getenv(t_general *all, char *var)
{
	t_list	*tmp;
	int		len;

	tmp = all->env[0];
	len = ft_strlen(var);
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->content, len)
			&& ((char *)tmp->content)[len] == '=')
			return ((char *)tmp->content + len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

int	export_new_env(t_general *all)
{
	t_list	*tmp;
	int		i;

	free_tab(&(all->new_env));
	all->new_env = ft_calloc(sizeof(char *), ft_lstsize(all->env[0]) + 1);
	if (!all->new_env)
		return (g_status = -2, -2);
	i = 0;
	tmp = all->env[0];
	while (tmp)
	{
		all->new_env[i] = ft_strdup(tmp->content);
		if (!all->new_env[i])
		{
			free_tab(&(all->new_env));
			return (-2);
		}
		tmp = tmp->next;
		i++;
	}
	all->address_envp[0] = all->new_env;
	return (0);
}
