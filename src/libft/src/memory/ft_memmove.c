/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:47:38 by pichatte          #+#    #+#             */
/*   Updated: 2023/05/31 18:52:47 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		dptr;
	size_t		sptr;
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (0);
	dptr = (long unsigned int) dest;
	sptr = (long unsigned int) src;
	d = (char *) dest;
	s = (char *) src;
	if (dptr - sptr >= n)
		dest = ft_memcpy(dest, src, n);
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}
