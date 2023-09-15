/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:26 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/12 18:54:28 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	dec_len(int n)
{
	int	dec_len;

	dec_len = 0;
	if (n < 0)
		dec_len++;
	while (n / 10)
	{
		dec_len++;
		n /= 10;
	}
	return (dec_len + 1);
}

int	unsigned_len(unsigned int n)
{
	int	unsigned_len;

	unsigned_len = 0;
	while (n / 10)
	{
		unsigned_len++;
		n /= 10;
	}
	return (unsigned_len + 1);
}
