/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:09:34 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/13 17:22:04 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_var(t_general *all, int i)
{
	char	*var;
	int		j;

	var = ft_strdup(all->address_envp[0][i]);
	if (!var)
		return (NULL);
	j = 0;
	while (var[j])
	{
		if (var[j] == '=')
			var[j] = 0;
		else
			j++;
	}
	return (var);
}

int	export_no_args(t_general *all)
{
	int		i;
	char	*value;
	char	*var;

	i = 0;
	while (all->address_envp[0] && all->address_envp[0][i])
	{
		value = ft_strchr_one(all->address_envp[0][i], '=');
		if (!value)
			return (1);
		var = find_var(all, i);
		if (!var)
			return (-2);
		ft_dprintf(1, "%s=\"%s\"\n", var, value);
		free(var);
		var = NULL;
		i++;
	}
	return (0);
}

static int	set_to_env(t_general *all, char **cmd_and_args)
{
	int		i;
	t_list	*exists;

	i = 1;
	while (cmd_and_args && cmd_and_args[i])
	{
		exists = node_in_env(all, cmd_and_args[i]);
		if (!exists)
		{
			ft_lstadd_back(all->env, ft_lstnew(ft_strdup(cmd_and_args[i])));
			if (!(ft_lstlast(all->env)) || !((ft_lstlast(all->env))->content))
				return (-2);
		}
		else
		{
			free(exists->content);
			exists->content = ft_strdup(cmd_and_args[i]);
			if (!exists->content)
				return (-2);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_general *all, char **cmd_and_args)
{
	int	size;
	int	ret;

	if (!cmd_and_args || !(*cmd_and_args)
		|| ft_strncmp(cmd_and_args[0], "export", ft_strlen("export") + 1))
		return (1);
	ret = 0;
	size = find_array_size(cmd_and_args);
	if (size == 1)
	{
		ret = export_no_args(all);
		if (ret != 0)
			return (ret);
	}
	else
	{
		ret = set_to_env(all, cmd_and_args);
		if (ret != 0)
			return (ret);
		ret = export_new_env(all);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

int	var_declared(t_general *all, t_token **var)
{
	int		cmp_len;
	t_list	*tmp;
	int		ret;

	if (!var || !var[0] || var[0]->type != VAR)
		return (0);
	ret = 0;
	cmp_len = 0;
	while ((var[0]->value)[cmp_len] && (var[0]->value)[cmp_len] != '=')
		cmp_len++;
	tmp = all->env[0];
	while (tmp)
	{
		if (!ft_strncmp(var[0]->value, tmp->content, cmp_len))
		{
			free(tmp->content);
			tmp->content = ft_strdup(var[0]->value);
			if (!tmp->content)
				return (-2);
			ret = export_new_env(all);
		}
		tmp = tmp->next;
	}
	(*var) = (*var)->next;
	return (ret);
}
