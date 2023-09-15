/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:45:52 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 15:29:30 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_free_exit_code(char *str, t_var *var, char *nb)
{
	free(str);
	free(var->value);
	free(nb);
}

char	*expand_exit_code(char *str, int j, t_var *var)
{
	char	*new;
	char	*nb;
	int		index;
	int		i;

	i = 0;
	index = 0;
	var->len_exp = malloc_len(g_status);
	new = malloc(ft_strlen(str) - var->len_var + var->len_exp + 1);
	if (!new)
		return (free(str), free(var->value), NULL);
	while (index < j)
	{
		new[index] = str[index];
		index++;
	}
	nb = ft_itoa(g_status);
	while (nb[i])
		new[index++] = nb[i++];
	j += 2;
	while (str[j])
		new[index++] = str[j++];
	new[index] = '\0';
	ft_free_exit_code(str, var, nb);
	return (new);
}

t_list	*ft_set_exit_var(t_var *var, t_list *current)
{
	var->value = malloc(2);
	if (!var->value)
		return (NULL);
	var->value[0] = '?';
	var->value[1] = '\0';
	return (current);
}
