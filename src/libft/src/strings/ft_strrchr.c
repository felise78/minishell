/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:05:10 by pichatte          #+#    #+#             */
/*   Updated: 2023/05/31 19:01:18 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len > 0 && s[len] != (unsigned char)(c))
	{
		len--;
	}
	if (s[len] == (unsigned char)(c))
	{
		return ((char *)(s + len));
	}
	else
		return (0);
}

char	*ft_strrchr_one(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len > 0 && s[len] != (unsigned char)(c))
	{
		len--;
	}
	if (s[len] == (unsigned char)(c))
	{
		return ((char *)(s + len + 1));
	}
	else
		return (0);
}
