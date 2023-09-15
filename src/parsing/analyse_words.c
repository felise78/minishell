/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:56:32 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 18:29:28 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_analyse_again(t_token **cmd_line)
{
	t_token	*current;

	current = *cmd_line;
	while (current)
	{
		if (current->type < VAR && current->next && current->next->type == VAR)
			current->next->type = ARG;
		if (current->type == VAR && current->next && current->next->type < VAR)
		{
			ft_tokendelone(cmd_line, current, &free);
			current = NULL;
			current = *cmd_line;
		}
		else
			current = current->next;
	}
}

void	ft_analyse_words(t_token **cmd_line)
{
	t_token	*current;
	int		cmd;

	cmd = 0;
	current = *cmd_line;
	while (current)
	{
		if (current->type == WORD && ft_check4var(current))
			current->type = VAR;
		else if (current->type >= HEREDOC)
		{
			current = current->next;
			current->type = ARG;
		}
		else if (current->type == WORD && cmd == 0)
		{
			current->type = CMD;
			cmd = 1;
		}
		else if (current->type == WORD && cmd == 1)
			current->type = ARG;
		else if (current->type == PIPE)
			cmd = 0;
		current = current->next;
	}
}
