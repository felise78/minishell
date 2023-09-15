/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:07:02 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 15:02:42 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int	checkvar_1stchar(char *str, int i)
{
	i--;
	while (i >= 0 && str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i--;
	if (i != 0)
		i++;
	if (ft_isalpha(str[i]))
		return (1);
	else
		return (0);
}

int	move_till_end_of_quotes(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] != quote)
		i++;
	return (i);
}

int	ft_check4var(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == 34 || token->value[i] == 39)
			i = move_till_end_of_quotes(token->value, i);
		if (token->value[i] == '='
			&& ft_isalnum(token->value[i - 1]))
		{
			if ((checkvar_1stchar(token->value, i)))
				return (1);
		}
		i++;
	}
	return (0);
}
