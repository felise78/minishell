/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_delimiters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:52:04 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 15:51:13 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	analyse_delimiter2(t_token **cmd_line, char c, char *new)
{
	new[0] = c;
	new[1] = '\0';
	if (c == '<')
	{
		if (!(create_token(cmd_line, REDIR_INPUT, new)))
			return (0);
	}
	else if (c == '>')
	{
		if (!(create_token(cmd_line, REDIR_OUTPUT, new)))
			return (0);
	}
	else if (c == '|')
	{
		if (!(create_token(cmd_line, PIPE, new)))
			return (0);
	}
	return (1);
}

int	analyse_delimiter(t_token **cmd_line, char *str, int i)
{
	char	*new;

	new = malloc(3);
	if (!new)
		return (0);
	if (is_redir(str[i]) && str[i] == str[i + 1])
	{
		new[0] = str[i];
		new[1] = str[i];
		new[2] = '\0';
		if (str[i] == '<')
		{
			if (!(create_token(cmd_line, HEREDOC, new)))
				return (free(new), new = NULL, 0);
		}
		else if (!(create_token(cmd_line, APPEND, new)))
			return (free(new), new = NULL, 0);
	}
	else if (is_redir(str[i]) || str[i] == '|')
	{
		if (!(analyse_delimiter2(cmd_line, str[i], new)))
			return (free(new), new = NULL, 0);
	}
	return (1);
}
