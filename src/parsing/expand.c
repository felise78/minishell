/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:47:25 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/14 17:50:15 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*replace_expand(char *str, int j, t_var *var, char *expand)
{
	char	*new;
	int		i;
	int		h;

	(void)expand;
	i = 0;
	h = 0;
	new = malloc(ft_strlen(str) - var->len_var + var->len_exp + 1);
	if (!new)
		return (free(str), free(var->value), free(var->expand), NULL);
	while (i < j)
	{
		new[i] = str[i];
		i++;
	}
	while (h < var->len_exp)
		new[i++] = var->expand[h++];
	j = j + var->len_var + 1;
	while (str[j])
		new[i++] = str[j++];
	new[i] = '\0';
	free(var->value);
	free(var->expand);
	free(str);
	return (new);
}

char	*remove_expand(char *str, int j, t_var *var)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(str) - var->len_var + 1);
	if (!new)
		return (free(str), NULL);
	while (i < j)
	{
		if (i == j - 1 && str[j - 1] == '$')
			i++;
		new[i] = str[i];
		i++;
	}
	j = j + var->len_var + 1;
	while (str[j])
		new[i++] = str[j++];
	new[i] = '\0';
	free(str);
	free(var->value);
	return (new);
}

int	ft_expand_inside_quotes(int i, t_token *token, t_general *all, t_var *var)
{
	char	quote;

	quote = token->value[i];
	i++;
	while (token->value[i] && token->value[i] != quote)
	{
		if (quote == 34 && token->value[i] == '$'
			&& !(is_space(token->value[i + 1])))
		{
			token->value = ft_expand_var(token->value, i, all, var);
			if (token->value == NULL)
				return (-1);
			i = i + var->len_exp;
		}
		i++;
	}	
	return (i);
}

int	ft_expand_token(t_token *token, t_general *all)
{	
	int		i;
	t_var	var;

	i = 0;
	while (token->value && token->value[i])
	{
		if (token->value[i] == 39 || token->value[i] == 34)
		{
			if (ft_expand_inside_quotes(i, token, all, &var) == -1)
				return (0);
			i = ft_expand_inside_quotes(i, token, all, &var);
		}
		else if (token->value[i] == '$' && !(is_space(token->value[i + 1])))
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

int	ft_check_if_expand(t_token **cmd_line, t_general *all)
{
	t_token		*current;

	current = *cmd_line;
	while (current)
	{
		if (current->type == HEREDOC)
			current = current->next;
		else if (current->type == WORD && is_var_to_expand(current->value))
		{
			if (!(ft_expand_token(current, all)))
				return (g_status = -2, 0);
			if (!current->value[0])
			{
				ft_tokendelone(cmd_line, current, &free);
				current = NULL;
				current = *cmd_line;
			}
		}
		else
			current = current->next;
	}
	return (1);
}
