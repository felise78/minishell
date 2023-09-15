/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:55:26 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/12 19:47:25 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_unset_2(t_general *all, t_list **tmp,
				char **cmd_and_args, int i);

void	use_free(void *content)
{
	free (content);
}

int	unset_errors(char **cmd_and_args)
{	
	if (!cmd_and_args
		|| ft_strncmp(cmd_and_args[0], "unset", ft_strlen("unset") + 1))
		return (1);
	if (check_option(cmd_and_args))
	{
		ft_dprintf(2, "Options are not permitted\n");
		return (2);
	}
	return (0);
}

int	ft_unset(t_general *all, char **cmd_and_args)
{
	t_list	*tmp;
	int		size;
	int		i;

	size = unset_errors(cmd_and_args);
	if (size)
		return (size);
	size = find_array_size(cmd_and_args);
	if (size >= 2)
	{
		i = 1;
		while (cmd_and_args[i])
		{	
			tmp = all->env[0];
			ft_unset_2(all, &tmp, cmd_and_args, i);
			if (cmd_and_args[i])
				i++;
		}
		if (export_new_env(all) != 0)
			return (1);
	}
	return (0);
}

static void	ft_unset_2(t_general *all, t_list **tmp, char **cmd_and_args, int i)
{
	char	*var;

	while ((*tmp) && cmd_and_args[i])
	{
		var = cmd_and_args[i];
		if (var && !ft_strncmp((*tmp)->content, var, ft_strlen(var))
			&& ((char *)(*tmp)->content + ft_strlen(var))[0] == '=')
		{
			ft_lstdelone(all->env, (*tmp), &use_free);
			i++;
			(*tmp) = all->env[0];
		}
		else
			(*tmp) = (*tmp)->next;
	}
}
