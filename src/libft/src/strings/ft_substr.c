/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:11 by pichatte          #+#    #+#             */
/*   Updated: 2023/04/14 18:09:07 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;

	if (!s)
		return (0);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start + i] && i < len)
			i++;
	}
	substr = (char *)malloc(sizeof(char) * (i + 1));
	if (!substr)
		return (0);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start + i] && i < len)
		{
			substr[i] = s[start + i];
			i++;
		}
	}
	substr[i] = 0;
	return (substr);
}
