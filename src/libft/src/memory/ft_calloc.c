/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:11:27 by pichatte          #+#    #+#             */
/*   Updated: 2023/05/31 18:51:09 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	str = NULL;
	if (!nmemb || !size || (size != 0 && nmemb < SIZE_MAX / size))
	{
		str = malloc(size * nmemb);
		if (!str)
			return (NULL);
	}
	if (str)
		ft_bzero(str, nmemb * size);
	return (str);
}
