/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:51:17 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 15:23:07 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_space(char c)
{
	return (c == '\f' || c == '\t' || c == '\r' || c == '\v' || c == 32);
}

int	is_redir(char c)
{
	return (c == '>' || c == '<');
}

int	len_until_delimiter(char *str, int i)
{
	int		j;
	char	quote;

	j = 0;
	while (str[i] && !is_space(str[i]) && !is_redir(str[i]) && str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote = str[i++];
			while (str[i++] != quote)
				++j;
			j++;
			i--;
		}
		i++;
		j++;
	}
	return (j);
}

int	ft_strchrstr(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i])
	{
		j = 0;
		while (str1[i] && str2[j] && str1[i] == str2[j])
		{
			if (j == (int)ft_strlen(str2) - 1)
				return (1);
			i++;
			j++;
		}
		i++;
	}
	return (0);
}
