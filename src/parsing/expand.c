/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:47:25 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/22 17:56:08 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_expand_inside_quotes(int i, t_token *token, t_general *all, t_var *var)
{
	char	quote;

	quote = token->value[i];
	if (token->value[i + 1] != quote)
		i++;
	else 
		return (i + 2);
	while (token->value[i] && token->value[i] != quote)
	{
		if (quote == 34 && token->value[i] == '$' && token->value[i - 1] == 34 && token->value[i + 1] == 34)
			i++;
		else if (token->value[i] == '$' && token->value [i + 1] && token->value [i + 1] == '$')
			i += 2;
		else if (quote == 34 && token->value[i] == '$'
			&& !(is_space(token->value[i + 1])))
		{
			token->value = ft_expand_var(token->value, i, all, var);
			if (token->value == NULL)
				return (-1);
			i = i + var->len_exp; //+ 1;
		}
		else 
			i++;
	}	
	return (i + 1);
}

int	move_to_end_of_quote(t_token *token, int i)
{
	i++;
	while(token->value[i] != 39)
		i++;
	i++;
	return (i);
}

int	ft_expand_token(t_token *token, t_general *all)
{	
	int		i;
	t_var	var;

	i = 0;
	while (token->value && token->value[i])
	{
		if (token->value[i] == '$' && token->value[i + 1] && token->value[i + 1] == '$')
			i += 2;
		else if (token->value[i] == 39)
			i = move_to_end_of_quote(token, i);
		else if (token->value[i] == 34)
		{
			if (ft_expand_inside_quotes(i, token, all, &var) == -1)
				return (0);
			i = ft_expand_inside_quotes(i, token, all, &var);
		}
		else if (token->value[i] == '$' && token->value[i + 1] && !(is_space(token->value[i + 1])))
		{
			token->value = ft_expand_var(token->value, i, all, &var);
			if (token->value == NULL)
				return (0);
			i = i + var.len_exp;
		}
		else
			i++;
	}
	return (1);
}

int	ft_check_if_expand(t_token **cmd_line, t_general *all, t_token *current)
{
	while (current)
	{
		if (current->type == HEREDOC)
			current = current->next->next;
		else if (current && current->type == WORD
			&& is_var_to_expand(current->value))
		{
			if (!(ft_expand_token(current, all)))
				return (g_status = -2, 0);
			else
			{
				if (current && !current->value[0])
				{
					ft_tokendelone(cmd_line, current, &free);
					current = NULL;
					current = *cmd_line;
				}
				else
					current = current->next;
			}
		}
		else
			current = current->next;
	}
	return (1);
}
