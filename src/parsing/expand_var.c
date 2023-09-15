/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:09 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/13 15:46:41 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_data_var(char *str, int j, t_var *var, t_list *in_env)
{
	int	i;

	i = 0;
	var->value = malloc(var->len_var + 1);
	if (!var->value)
		return (0);
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '?' || str[j] == '_'))
	{
		var->value[i] = str[j];
		j++;
		i++;
	}
	var->value[i] = '\0';
	i = 0;
	var->len_exp = ft_expand_len(in_env, var);
	var->expand = malloc(var->len_exp + 1);
	if (!var->expand)
		return (free(var->value), var->value = NULL, 0);
	ft_copy_expand(var, (char *)in_env->content);
	return (1);
}

t_list	*ft_is_variable_in_env(char *str, int i, t_general *all, t_var *var)
{
	char	*ptr;
	t_list	*current;

	current = *all->env;
	if (str[i] == '$')
		i++;
	var->len_var = ft_len_variable(str, i);
	if (str[i] == '?' && !ft_isalnum(str[i + 1]))
		return (ft_set_exit_var(var, current));
	while (current)
	{
		ptr = (char *)current->content;
		if (ft_strcmpenv(str, i, ptr, var->len_var) != 0)
			current = current->next;
		else
		{
			ft_data_var(str, i, var, current);
			return (current);
		}
	}
	return (NULL);
}

char	*ft_expand_var(char *str, int i, t_general *all, t_var *var)
{
	t_list	*in_env;

	var->value = NULL;
	var->expand = NULL;
	var->len_exp = 0;
	var->len_var = 0;
	in_env = ft_is_variable_in_env(str, i, all, var);
	if (ft_strchrstr(var->value, "?"))
		str = expand_exit_code(str, i, var);
	else if (in_env && (var->value == NULL || var->expand == NULL))
		return (free(str), NULL);
	else if (!in_env)
	{
		str = remove_expand(str, i, var);
		if (!str)
			return (NULL);
	}
	else if (in_env)
	{
		str = replace_expand(str, i, var, (char *)in_env->content);
		if (!str)
			return (NULL);
	}
	return (str);
}
