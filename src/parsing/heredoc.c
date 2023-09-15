/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:57:56 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/14 17:06:46 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*heredoc_expand(char *buffer, t_general *all)
{
	int		i;
	t_var	var;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$' && (ft_isalnum(buffer[i + 1])
				|| buffer[i + 1] == '?' || buffer[i + 1] == '_'))
		{
			buffer = ft_expand_var(buffer, i, all, &var);
			i = i + var.len_exp;
		}
		i++;
	}
	return (buffer);
}

void	close_heredoc(char *buffer, char *line, int *fd, int nb)
{
	if (nb > 1)
		close(fd[0]);
	close(fd[1]);
	if (line)
		free(line);
	if (buffer)
		free (buffer);
}

char	*ft_heredoc(char *buffer, char *line, char *delimiter)
{
	line = readline("> ");
	if (!line)
		return (free(buffer), warning_eof(delimiter), g_status = 0, NULL);
	while (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
	{
		line = ft_strjoin_free(line, "\n", 1);
		if (!line)
			return (g_status = -2, NULL);
		buffer = ft_strjoin_free(buffer, line, 1);
		if (!buffer)
			return (free (line), g_status = -2, NULL);
		free(line);
		line = readline("> ");
		if (!line)
			return (free(buffer), warning_eof(delimiter), g_status = 0, NULL);
	}
	return (free(line), line = NULL, buffer);
}

int	ft_set_heredoc(t_token *current, int *fd, int nb, t_general *all)
{
	char	*delimiter;
	char	*buffer;
	char	*line;

	buffer = NULL;
	line = NULL;
	if (pipe(fd) == -1)
		return (g_status = 2, perror("heredoc pipe fail\n"), 0);
	delimiter = current->next->value;
	signal(SIGINT, &handler_heredoc);
	buffer = ft_heredoc(buffer, line, delimiter);
	if (nb == 1 && ft_strchr(buffer, '$') && is_var_to_expand(buffer))
		buffer = heredoc_expand(buffer, all);
	ft_putstr_fd(buffer, fd[1]);
	close_heredoc(buffer, line, fd, nb);
	return (1);
}

int	ft_check_if_heredoc(t_token **cmd_line, t_general *all)
{
	t_token	*current;
	int		i;
	int		*fd;
	int		nb_heredocs;

	i = 0;
	current = *cmd_line;
	while (current)
	{
		fd = all->all_cmds[i].here_fd;
		nb_heredocs = heredoc_count(current);
		if (current->type == HEREDOC && current->next
			&& current->next->type == WORD)
		{
			if (ft_set_heredoc(current, fd, nb_heredocs, all) == 0)
				return (0);
		}
		else if (current->type == PIPE)
			i++;
		current = current->next;
	}
	return (1);
}
