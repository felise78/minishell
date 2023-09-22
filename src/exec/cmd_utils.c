/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:04:12 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/18 14:29:53 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_exec_array_size(t_token **cmdline)
{
	int		i;
	int		cmd_found;
	t_token	*tmp;

	i = 0;
	tmp = (*cmdline);
	cmd_found = 0;
	while (tmp && tmp->type != PIPE)
	{
		while (tmp && cmd_found == 0)
		{
			if (tmp->type == CMD)
				cmd_found = 1;
			tmp = tmp->next;
		}
		if (!tmp)
			break ;
		if (tmp && tmp->type == ARG)
			i++;
		if (tmp)
			tmp = tmp->next;
	}
	return (i);
}

static int	ft_malloc_cmd_and_args(t_general *all, t_token **cmd_line, int i)
{
	int		j;

	if (!cmd_line || !(*cmd_line))
		return (1);
	j = find_exec_array_size(cmd_line);
	all->all_cmds[i].cmd_args = ft_calloc(sizeof(char *), j + 2);
	if (!(all->all_cmds[i].cmd_args))
		return (-2);
	return (0);
}

static int	is_redirection(t_general *all, t_token **cmdline, int i)
{	
	t_token	*new;
	int		ret;

	if (!(*cmdline) || !((*cmdline)->next))
		return (0);
	if ((*cmdline)->type < HEREDOC)
		return (0);
	ret = 0;
	if ((*cmdline)->type > HEREDOC || is_last_heredoc(&(*cmdline)))
	{
		new = ft_token_new(ft_strdup((*cmdline)->next->value),
				(*cmdline)->type);
		if (!new || !(new->value))
			return (-2);
		ret = set_redir_lists(&(all->all_cmds[i].redirections), new);
		if ((*cmdline)->type >= HEREDOC && (*cmdline)->next)
			*cmdline = (*cmdline)->next->next;
	}
	if ((*cmdline) && (*cmdline)->type == HEREDOC
		&& !is_last_heredoc(&(*cmdline)) && (*cmdline)->next)
		*cmdline = (*cmdline)->next->next;
	return (ret);
}

static int	set_cmds_loop(t_general *all, t_token **tmp, int *i, int j)
{
	int	ret;

	j = 0;
	ret = 0;
	while (*tmp && (*tmp)->type != PIPE)
	{
		while ((*tmp && (*tmp)->type == CMD) || (*tmp && (*tmp)->type == ARG))
		{
			all->all_cmds[*i].cmd_args[j] = ft_strdup((*tmp)->value);
			if (!(all->all_cmds[*i].cmd_args[j]))
				return (-2);
			*tmp = (*tmp)->next;
			j++;
		}
		ret = var_declared(all, &(*tmp));
		if (ret != 0)
			return (ret);
		ret = is_redirection(all, tmp, *i);
		if (ret != 0)
			return (ret);
	}
	if (*tmp)
		*tmp = (*tmp)->next;
	(*i)++;
	return (0);
}

int	parse_cmdline(t_general *all, t_token **cmdline)
{
	t_token	*tmp;
	int		i;
	int		j;
	int		ret;

	i = 0;
	ret = 0;
	tmp = *cmdline;
	while (tmp)
	{	
		ret = ft_malloc_cmd_and_args(all, &tmp, i);
		if (ret != 0)
			return (ret);
		j = 0;
		ret = set_cmds_loop(all, &tmp, &i, j);
		if (ret != 0)
			return (ret);
	}
	return (ret);
}
