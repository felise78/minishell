/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:46:21 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/12 19:00:35 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_addcount(const char *str, int i, va_list copy)
{
	va_list	null_copy;

	va_copy(null_copy, copy);
	if (str[i] == 'c' || str[i] == '%')
		return (1);
	if (str[i] == 's' && !va_arg(null_copy, char *))
		return (6);
	if (str[i] == 's')
		return (ft_strlen(va_arg(copy, char *)));
	if (str[i] == 'd' || str[i] == 'i')
		return (dec_len(va_arg(copy, int)));
	if (str[i] == 'x' || str[i] == 'X')
		return (hex_len(va_arg(copy, unsigned int)));
	if (str[i] == 'p')
	{
		if (!va_arg(null_copy, unsigned long))
			return (5);
		else
			return (2 + hex_len(va_arg(copy, unsigned long)));
	}
	if (str[i] == 'u')
		return (unsigned_len(va_arg(copy, unsigned int)));
	else
		return (0);
}

static void	printf_putstring(va_list args, int fd)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		ft_putstr_fd("(null)", fd);
	else
		ft_putstr_fd(str, fd);
}

static int	ft_checkvar(const char *str, int i, va_list args, t_printf ints)
{
	va_list	copy;

	i++;
	va_copy(copy, args);
	ints.count += ft_addcount(str, i, copy);
	if (str[i] == 'c')
		ft_putchar_fd(va_arg(args, int), ints.fd);
	if (str[i] == 's')
		printf_putstring(args, ints.fd);
	if (str[i] == 'd' || str[i] == 'i')
		ft_putnbr_fd(va_arg(args, int), ints.fd);
	if (str[i] == 'x')
		ft_puthex_lower(va_arg(args, unsigned int), ints.fd);
	if (str[i] == 'X')
		ft_puthex_upper(va_arg(args, unsigned int), ints.fd);
	if (str[i] == 'p')
		ft_putptr(va_arg(args, unsigned long), ints.fd);
	if (str[i] == 'u')
		ft_putunsigned(va_arg(args, unsigned int), ints.fd);
	if (str[i] == '%')
		ft_putchar_fd('%', ints.fd);
	return (ints.count);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	t_printf	ints;
	int			i;
	va_list		args;

	va_start(args, str);
	ints.count = 0;
	ints.fd = fd;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ints.count = ft_checkvar(str, i, args, ints);
			i++;
		}
		else
		{
			write(fd, &str[i], 1);
			(ints.count)++;
		}
		i++;
	}
	va_end(args);
	return (ints.count);
}
