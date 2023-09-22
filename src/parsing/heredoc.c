/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:57:56 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/22 17:28:10 by hemottu          ###   ########.fr       */
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

void	close_heredoc(char *line, int *fd, int nb)
{
	if (nb > 1)
	{	
		if (close(fd[0]) == -1) // pas de return ? 
		{
			perror("fd[0]");
			g_status = 2;
		}
		fd[0] = -1;
	}
	if (close(fd[1]) == -1)
	{
		perror("fd[1]");
		g_status = 2;
	}
	fd[1] = -1;
	g_status = 0;
	if (line)
		free(line);
}

int ft_heredoc(t_general *all, char *line, char *delimiter, int *fd)
{
	line = readline("> ");
	if (!line && g_status != 130)
		return (warning_eof(delimiter), g_status = 0, 1);
	else if (!line)
		return (0);
	while (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
	{
		line = ft_strjoin_free(line, "\n", 1);
		if (!line)
			return (g_status = -2, 0);
		if (ft_strchr(line, '$') && is_var_to_expand(line))
			line = heredoc_expand(line, all);
		ft_putstr_fd(line, fd[1]);
		free(line);
		g_status = 0;
		line = readline("> ");
		if (!line && g_status != 130)
			return (warning_eof(delimiter), g_status = 0, 1);
		else if (!line)
			return (0);
	}
	return (free(line), line = NULL, 1);
}

int	ft_set_heredoc(t_token *current, int *fd, int nb, t_general *all)
{
	char	*delimiter;
	char	*line;

	line = NULL;
	all->fd_tmp = dup(STDIN_FILENO); // a proteger
	if (all->fd_tmp == -1)
		return (g_status = 2, perror("fd_tmp"), 0);
	if (pipe(fd) == -1)
		return (g_status = 2, perror("heredoc pipe fail\n"), 0);
	delimiter = current->next->value;
	signal(SIGINT, &handler_heredoc);
	g_status = 0;
	if (!(ft_heredoc(all, line, delimiter, fd)))
	{
		if (g_status == 130)
			dup2(all->fd_tmp, STDIN_FILENO);
		return (0);
	}
	close_heredoc(line, fd, nb);
	if (close(all->fd_tmp) == -1)
		return (g_status = 2, perror("fd_tmp"), 0);
	all->fd_tmp = -1;
	if (g_status != 0)
		return (0);
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
