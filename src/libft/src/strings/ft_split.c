/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:01:51 by pichatte          #+#    #+#             */
/*   Updated: 2023/05/31 19:10:24 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_malloc(char **strs, size_t num)
{
	while (num > 0)
	{
		free((char *)(strs[num - 1]));
		num--;
	}
	free(strs);
	return ;
}

size_t	num_words(char const *s, char c)
{
	size_t	num;
	size_t	i;

	i = 0;
	num = 0;
	while (s[i])
	{
		if ((i != 0 && s[i] == c && s[i - 1] != c)
			|| (s[i] != c && s[i + 1] == 0))
			num++;
		i++;
	}
	return (num);
}

static char	*create_str(const char *start, char c, char **strs, size_t num)
{
	char	*str;
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (start[len] != c && start[len] != 0)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
	{	
		free_malloc(strs, num);
		return (NULL);
	}
	while (start[i] != c && start[i] != 0)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static char	**split_words(char const *s, char c, char **strs)
{
	size_t	num;
	size_t	i;
	size_t	index;

	i = 0;
	num = 0;
	while (s[i])
	{
		if ((s[0] != c && i == 0) || (s[i] != c && s[i - 1] == c))
			index = i;
		if ((i != 0 && s[i] == c && s[i - 1] != c)
			|| (s[i] != c && s[i + 1] == 0))
		{
			strs[num] = create_str(s + index, c, strs, num);
			if (!strs[num])
				return (NULL);
			num++;
		}
		i++;
	}
	strs[num] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (num_words(s, c) + 1));
	if (!strs)
		return (NULL);
	strs = split_words(s, c, strs);
	return (strs);
}
