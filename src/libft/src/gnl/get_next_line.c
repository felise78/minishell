/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:40:32 by pichatte          #+#    #+#             */
/*   Updated: 2023/05/31 18:57:24 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_line(char *save)
{
	size_t	i;
	char	*line;

	if (!save)
		return (0);
	line = NULL;
	i = 0;
	while ((save[i]))
	{
		if (save[i] == '\n' || !(save[i + 1]))
		{
			line = (char *)malloc(sizeof(char) * (i + 2));
			if (!line)
				return (0);
			ft_strcpy(line, save, i);
			return (line);
		}
		i++;
	}
	return (line);
}

static int	no_line_in_save(char *save)
{
	size_t	i;

	i = 0;
	if (!save)
		return (1);
	while (save[i])
	{
		if (save[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

void	free_line(char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*save;
	char		*line;
	int			done;

	done = 1;
	while (done && no_line_in_save(save))
	{
		buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return (0);
		done = read(fd, buffer, BUFFER_SIZE);
		if (done == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[done] = 0;
		save = ft_strjoin_gnl(save, &buffer);
	}
	line = return_line(save);
	save = ft_strchr_gnl(&save, '\n', &done);
	if (!line && save)
		free_line(&save);
	return (line);
}
