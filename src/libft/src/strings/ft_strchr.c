/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:09:11 by pichatte          #+#    #+#             */
/*   Updated: 2023/08/30 15:25:25 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != (unsigned char)(c) && s[i])
	{
		i++;
	}
	if (s[i] == (unsigned char)(c))
	{	
		return ((char *)(s + i));
	}
	else
		return (NULL);
}

/* THIS STRCHR RETURNS THE LOCATION OF C + 1*/
char	*ft_strchr_one(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != (unsigned char)(c) && s[i])
	{
		i++;
	}
	if (s[i] == (unsigned char)(c))
	{	
		return ((char *)(s + i + 1));
	}
	else
		return (NULL);
}
