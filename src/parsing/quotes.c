/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:48:13 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 15:23:34 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int	is_quote_closed(char *str)
{
	bool	closed;
	int		i;
	int		quote;

	i = 0;
	closed = true;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == 39 || str[i] == 34)
		{
			quote = str[i];
			closed = false;
			i++;
			while (i < (int)ft_strlen(str) && str[i] != quote)
				i++;
			if (str[i++] == quote)
				closed = true;
		}
		else
			i++;
	}
	return (closed);
}

char	*ft_remove_quotes(t_token *current, int i, int j)
{
	char	*new;

	new = malloc(ft_strlen(current->value));
	if (!new)
		return (free(current->value), current->value = NULL, NULL);
	while (current->value[i])
	{
		if (current->value[i] == 39)
		{
			i++;
			while (current->value[i] != 39)
				new[j++] = current->value[i++];
		}
		else if (current->value[i] == 34)
		{
			i++;
			while (current->value[i] != 34)
				new[j++] = current->value[i++];
		}
		else
			new[j++] = current->value[i];
		i++;
	}
	new[j] = '\0';
	return (free(current->value), new);
}

int	ft_parse4quotes(t_token **cmd_line)
{
	t_token	*current;
	char	*new;

	current = *cmd_line;
	while (current)
	{
		if ((current->type == CMD || current->type == ARG)
			&& (ft_strchr(current->value, 34)
				|| ft_strchr(current->value, 39)))
		{
			new = ft_remove_quotes(current, 0, 0);
			if (!new)
				return (0);
			current->value = ft_strdup(new);
			free(new);
		}
		current = current->next;
	}
	return (1);
}
