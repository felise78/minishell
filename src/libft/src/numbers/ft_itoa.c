/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:59:14 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/13 15:29:53 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	malloc_len(int n)
{
	int				len;
	unsigned int	a;

	len = 0;
	a = 0;
	if (n < 0)
	{
		len++;
		a = -n;
	}
	else
		a = n;
	while (a >= 10)
	{
		len++;
		a /= 10;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char			*num;
	int				len;
	unsigned int	a;

	len = malloc_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (n < 0)
	{
		a = -n;
		num[0] = '-';
	}
	else
		a = n;
	while (a / 10)
	{
		num[--len] = (a % 10) + '0';
		a /= 10;
	}
	num[--len] = (a % 10) + 48;
	return (num);
}
