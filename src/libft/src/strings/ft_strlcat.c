/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:02:27 by pichatte          #+#    #+#             */
/*   Updated: 2022/11/22 16:36:32 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	if ((!src && !size) || (!dst && !size))
		return (0);
	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	else if (size <= dst_len)
		return (src_len + size);
	else
	{
		while (src[i] != 0 && (dst_len + i) < size - 1)
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		if (size > i)
			dst[dst_len + i] = 0;
		return (dst_len + src_len);
	}
}
