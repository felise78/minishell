/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:44:43 by pichatte          #+#    #+#             */
/*   Updated: 2023/04/14 18:09:01 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (c != set[i] && set[i])
		i++;
	if (set[i] == 0)
		return (0);
	else
		return (1);
}

static int	find_index(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (char_in_set(s1[i], set))
			i++;
	if (s1[i] == 0)
		return (-1);
	else
		return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		s_len;

	if (!s1)
		return (0);
	s_len = ft_strlen(s1);
	start = find_index(s1, set);
	while ((s_len - 1) && char_in_set(s1[s_len - 1], set))
		s_len--;
	i = 0;
	while (start + i != s_len && start >= 0)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == 0)
		return (0);
	i = 0;
	while (start + i != s_len && start >= 0)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
