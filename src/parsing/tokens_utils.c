/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:42:51 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/14 17:46:05 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_syntax_error(t_type type)
{
	g_status = 2;
	if (type == REDIR_INPUT)
		ft_putstr_fd("syntax error near unexpected token \'<\'\n", 2);
	else if (type == REDIR_OUTPUT)
		ft_putstr_fd("syntax error near unexpected token \'>\'\n", 2);
	else if (type == HEREDOC)
		ft_putstr_fd("syntax error near unexpected token \'<<\'\n", 2);
	else if (type == APPEND)
		ft_putstr_fd("syntax error near unexpected token \'>>\'\n", 2);
	else if (type == PIPE)
		ft_putstr_fd("syntax error near unexpected token \'|\'\n", 2);
}

void	ft_tokendelone(t_token **cmd_line, t_token *token, void (*del)(void *))
{
	t_token	*tmp;

	tmp = *cmd_line;
	if (!cmd_line || !token)
		return ;
	if (token == *cmd_line)
		*cmd_line = (*cmd_line)->next;
	else
	{
		while (tmp)
		{
			if (tmp->next == token)
			{
				tmp->next = token->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (del)
	{
		(*del)(token->value);
		token->value = NULL;
	}
	free(token);
}

t_token	*ft_token_new(char *str, t_type type)
{
	t_token	*newlst;

	newlst = (t_token *)malloc(sizeof(t_token));
	if (!newlst)
		return (NULL);
	newlst->value = str;
	newlst->type = type;
	newlst->next = NULL;
	return (newlst);
}

t_token	*ft_token_last(t_token *list)
{
	if (!list)
		return (NULL);
	while (list)
	{
		if (list->next == NULL)
			return (list);
		list = list->next;
	}
	return (list);
}

void	ft_token_add_back(t_token **list, t_token *new)
{
	t_token	*avdernier;

	if (!list)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		avdernier = ft_token_last(*list);
		avdernier->next = new;
	}
}
