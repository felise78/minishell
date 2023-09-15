/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:10:03 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/12 20:10:42 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_array_size(char **array)
{
	int	i;

	if (!array)
		return (-1);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**copy_tab(char **tab)
{
	char	**new;
	int		size;
	int		i;

	size = find_array_size(tab);
	if (size < 0)
		return (NULL);
	new = ft_calloc(sizeof(char *), size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
		{
			free_tab(&new);
			return (NULL);
		}
		i++;
	}
	return (new);
}
