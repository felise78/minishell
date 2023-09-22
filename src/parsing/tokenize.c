/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:50:44 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/21 14:58:44 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_check_last(t_token **cmd_line)
{
	t_token	*current;

	current = ft_token_last(*cmd_line);
	if (current->type >= PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token \'newline\'\n", 2);
		g_status = 2;
		return (0);
	}
	return (1);
}

int	ft_check_syntax_tokens(t_token **cmd_line)
{
	t_token	*current;

	current = *cmd_line;
	if (!current)
		return (0);
	if (current->type == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token \'|\'\n", 2);
		g_status = 2;
		return (0);
	}
	while (current)
	{
		if (current->next && (current->type == PIPE
				&& current->next->type == PIPE))
		{
			ft_putstr_fd("syntax error near unexpected token \'|\'\n", 2);
			g_status = 2;
			return (0);
		}
		else if (current->next && (current->type >= HEREDOC
				&& current->next->type >= PIPE))
			return (print_syntax_error(current->next->type), 0);
		current = current->next;
	}
	if (!(ft_check_last(cmd_line)))
		return (0);
	return (1);
}

int	token_word(t_token **cmd_line, char *str, int i)
{
	char	*new;
	int		j;
	int		len;

	j = 0;
	len = len_until_delimiter(str, i);
	new = malloc(len + 1);
	if (!new)
		return (0);
	while (j < len)
		new[j++] = str[i++];
	new[j] = '\0';
	if (!(create_token(cmd_line, WORD, new)))
		return (free(new), new = NULL, 0);
	return (1);
}

int	create_token(t_token **cmd_line, t_type type, char *str)
{
	t_token	*new;

	new = ft_token_new(str, type);
	if (!new)
		return (0);
	ft_token_add_back(cmd_line, new);
	return (1);
}

int	ft_lexer(t_token **cmd_line, char *str, int i)
{
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i] && (is_redir(str[i]) || str[i] == '|'))
		{
			if (!(analyse_delimiter(cmd_line, str, i)))
				return (0);
			if (is_redir(str[i]) && str[i] == str[i + 1])
				i++;
			i++;
		}
		else if (str[i] && !(is_space(str[i])))
		{
			if (!(token_word(cmd_line, str, i)))
				return (0);
			i = i + len_until_delimiter(str, i);
		}
	}
	return (1);
}

// fonction qui dit juste qui est quoi en printant :

// void ft_lexer(t_token *cmd_line, char *str)
// {
// 	int	i;
// 	int index;

// 	i = 0;
// 	index = 0;
// 	while (str[i])
// 	{
// 		if (is_space(str[i]))
// 		{
// 			printf("space ");
// 			while(str[i] && is_space(str[i]))
// 				i++;
// 		}
// 		else if (is_redir(str[i]) && str[i] == str[i + 1])
// 		{
// 			printf("double_redir ");
// 			i += 2;
// 		}
// 		else if (is_redir(str[i]))
// 		{
// 			printf("redir ");
// 			i++;
// 		}
// 		else if (str[i] == '|')
// 		{
// 			printf("pipe ");
// 			i++;
// 		}
// 		else if (str[i] == '-')
// 		{
// 			printf("option ");
// 			i = i + len_until_delimiter(str, i);
// 		}
// 		else
// 		{
// 			printf("word ");
// 			i = i + len_until_delimiter(str, i);
// 		}
// 	}
// 	printf("\n");
//  }
