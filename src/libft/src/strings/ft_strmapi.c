/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:21:51 by pichatte          #+#    #+#             */
/*   Updated: 2022/11/22 16:37:20 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s)
		return (0);
	str = ft_strdup(s);
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
