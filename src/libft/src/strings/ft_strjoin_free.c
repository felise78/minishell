/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:20:40 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 17:42:12 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char const *src, size_t dest_len)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[((int)dest_len) + i] = src[i];
		i++;
	}
	dest[((int)dest_len) + i] = 0;
	return (dest);
}

char	*ft_strjoin_free(char *s1, char *s2, int n)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
	{
		if (n == 1)
			free (s1);
		if (n == 2)
			free (s2);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	str = ft_strcat(str, s2, s1_len);
	if (n == 1)
		free(s1);
	if (n == 2)
		free(s2);
	return (str);
}
