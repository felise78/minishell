/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bourdon <bourdon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:24:27 by pichatte          #+#    #+#             */
/*   Updated: 2023/08/28 12:21:41 by bourdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunsigned(unsigned int i, int fd)
{
	while (i >= 10)
	{
		ft_putunsigned(i / 10, fd);
		i = i % 10;
	}
	ft_putchar_fd(i + 48, fd);
}
