/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bourdon <bourdon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:38:12 by pichatte          #+#    #+#             */
/*   Updated: 2023/08/28 12:18:39 by bourdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hex_len(unsigned long n)
{
	int	hex_len;

	hex_len = 0;
	while (n / 16)
	{
		hex_len++;
		n /= 16;
	}
	return (hex_len + 1);
}

void	ft_puthex_lower(unsigned int a, int fd)
{
	char	*base_lower;

	base_lower = "0123456789abcdef";
	while (a >= 16)
	{
		ft_puthex_lower(a / 16, fd);
		a = a % 16;
	}
	ft_putchar_fd(base_lower[a], fd);
}

void	ft_puthex_upper(unsigned int a, int fd)
{
	char	*base_upper;

	base_upper = "0123456789ABCDEF";
	while (a >= 16)
	{
		ft_puthex_upper(a / 16, fd);
		a = a % 16;
	}
	ft_putchar_fd(base_upper[a], fd);
}
