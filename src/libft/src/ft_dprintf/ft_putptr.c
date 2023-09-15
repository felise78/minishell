/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bourdon <bourdon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:51:56 by pichatte          #+#    #+#             */
/*   Updated: 2023/08/28 12:20:45 by bourdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_puthex_ptr(unsigned long a, int fd)
{
	char	*base_lower;

	base_lower = "0123456789abcdef";
	while (a >= 16)
	{
		ft_puthex_ptr(a / 16, fd);
		a = a % 16;
	}
	ft_putchar_fd(base_lower[a], fd);
}

void	ft_putptr(unsigned long a, int fd)
{
	if (!a)
	{
		ft_putstr_fd("(nil)", fd);
		return ;
	}
	write(fd, "0x", 2);
	ft_puthex_ptr(a, fd);
}
