/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:03:41 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/14 18:21:35 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_copy_expand(t_var *var, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return ;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i])
		var->expand[j++] = str[i++];
	var->expand[j] = '\0';
}

int	is_var_to_expand(char *str)
{
	int	i;
	int	nb_vars;

	i = 0;
	nb_vars = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
		}
		// if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
		// 		|| str[i + 1] == '?' || str[i + 1] == '_'))
		if (str[i] == '$' && str[i + 1] && !is_space(str[i + 1]))
			nb_vars++;
		i++;
	}
	return (nb_vars);
}

int	ft_len_variable(char *str, int i)
{
	int	j;

	j = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '?' || str[i] == '_'))
	{
		i++;
		j++;
	}
	return (j);
}

int	ft_strcmpenv(char *str, int index, char *env, int len)
{
	int	i;

	i = 0;
	if (!len)
		return (-1);
	if (str[index] == '$')
		index++;
	while (str[index] && env[i] && (str[index] == env[i]) && (i < len))
	{	
		index++;
		i++;
	}
	if (env[i] == 61 && (!str[index] || !(ft_isalnum(str[index]))))
		return (0);
	else
		return (-1);
}

int	ft_expand_len(t_list *in_env, t_var *var)
{
	char	*ptr;

	ptr = (char *)in_env->content;
	while (*ptr && *ptr != '=')
		ptr++;
	ptr++;
	while (*ptr)
	{
		var->len_exp++;
		ptr++;
	}
	return (var->len_exp);
}
