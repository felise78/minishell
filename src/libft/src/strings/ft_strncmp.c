/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:45:06 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/19 18:01:26 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*a1;
	const unsigned char	*a2;

	if (!s1 || !s2)
		return (-1);
	a1 = (unsigned char *) s1;
	a2 = (unsigned char *) s2;
	i = 0;
	while ((a1[i] && i < n) || (a2[i] && i < n))
	{	
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (a1[i] - a2[i]);
}
