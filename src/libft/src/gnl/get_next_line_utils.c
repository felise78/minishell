/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bourdon <bourdon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:40:53 by pichatte          #+#    #+#             */
/*   Updated: 2023/05/30 13:28:34 by bourdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_gnl(char **s, int c, int *i)
{
	int		j;
	char	*new_s;

	if (!*s)
		return (NULL);
	*i = 0;
	while ((*s)[*i] != c && (*s)[*i])
		(*i)++;
	if ((*s)[*i] == c && (*s)[(*i) + 1])
	{
		new_s = (char *)malloc(sizeof(char) * ((ft_strlen((*s))) - *i));
		if (!new_s)
			return (NULL);
		j = 0;
		while ((*s)[++*i])
			new_s[j++] = (*s)[*i];
		new_s[j] = 0;
		free_line(s);
		return (new_s);
	}
	else
	{
		free_line(s);
		return (NULL);
	}
}

void	ft_strcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	if (!dst || !src)
		return ;
	i = 0;
	while (i <= n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

void	ft_strcat_gnl(char *dest, char const *src)
{
	int	i;
	int	dest_len;

	if (!dest || !src)
		return ;
	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = 0;
}

char	*ft_strjoin_gnl(char *s1, char **s2)
{
	char	*str;

	if (!(s1))
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	str = (char *)malloc(sizeof(char) * ((ft_strlen(s1))
				+ (ft_strlen(*s2)) + 1));
	if (!str)
		return (0);
	ft_strcpy(str, s1, ft_strlen(s1) - 1);
	ft_strcat_gnl(str, *s2);
	if (s1)
		free_line(&s1);
	free_line(s2);
	return (str);
}
