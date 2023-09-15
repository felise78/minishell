/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:20:19 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/12 19:31:39 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*locate_cmd(t_token **cmd_line)
{
	t_token	*tmp;

	if (!cmd_line)
		return (NULL);
	tmp = *cmd_line;
	while (tmp)
	{
		if (tmp && tmp->type == CMD)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

int	is_builtin(t_token *token)
{
	if (!ft_strncmp(token->value, "echo", ft_strlen("echo") + 1))
		return (b_echo);
	if (!ft_strncmp(token->value, "env", ft_strlen("env") + 1))
		return (b_env);
	if (!ft_strncmp(token->value, "cd", ft_strlen("cd") + 1))
		return (b_cd);
	if (!ft_strncmp(token->value, "pwd", ft_strlen("pwd") + 1))
		return (b_pwd);
	if (!ft_strncmp(token->value, "export", ft_strlen("export") + 1))
		return (b_export);
	if (!ft_strncmp(token->value, "unset", ft_strlen("unset") + 1))
		return (b_unset);
	if (!ft_strncmp(token->value, "exit", ft_strlen("exit") + 1))
		return (b_exit);
	return (b_other);
}

int	check_option(char **cmd_and_args)
{
	int	i;

	if (!cmd_and_args)
		return (-1);
	i = 0;
	while (cmd_and_args[i])
	{
		if (ft_strchr(cmd_and_args[i], '-') == cmd_and_args[i])
			return (1);
		i++;
	}
	return (0);
}
