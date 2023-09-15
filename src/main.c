/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:07:05 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 19:39:08 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_parsing(char *str, t_token **cmd_line, t_general *all)
{
	// if (!str || !str[0])
	// 	return (0);
	if (!(is_quote_closed(str)))
	{
		ft_putstr_fd("minishell : syntax error : quote not closed\n", 2);
		g_status = 2;
		return (0);
	}
	if (!(ft_lexer(cmd_line, str, 0)))
		return (g_status = -2, 0);
	if (!(ft_init_pipes(all, cmd_line)))
		return (g_status = -2, 0);
	if (!(ft_check_if_heredoc(cmd_line, all))
		|| !(ft_check_syntax_tokens(cmd_line))
		|| !(ft_check_if_expand(cmd_line, all)))
		return (0);
	ft_analyse_words(cmd_line);
	ft_analyse_again(cmd_line);
	if (!(ft_parse4quotes(cmd_line)))
		return (g_status = -2, 0);
	return (1);
}

int	readline_loop(t_general *all, t_token **cmdline)
{
	char	*str;
	int		ret;

	ft_signals_parent();
	str = NULL;
	while (g_status != -2 && g_status != 254)
	{
		free(str);
		str = readline("minishell$ ");
		if (!str)
			return (handle_eof(all));
		all->cmdline[0] = NULL;
		if ((str)[0] != 0 && ft_strlen(str))
		{
			add_history(str);
			ret = main_parsing(str, cmdline, all);
			if (ret == 0)
			{
				free_and_set_null(all);
				printf("exit code: %d\n", g_status); ///
				continue ;
			}
			ret = ft_fork(all, all->cmdline);
			free_and_set_null(all);
			printf("exit code: %d\n", g_status); ///
		}
	}
	return (g_status);
}

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_general	all;
	t_pipe		pipeline;
	t_list		*env;
	t_token		*cmd_line;

	if (argc != 1)
		return (ft_dprintf(2, "This programme does not take arguments\n"), 1);
	if (!isatty(0))
		return (printf("Usage: ./minishell\n"), 0);
	(void)argv;
	env = NULL;
	all.address_envp = &envp;
	set_pointers(&all, &pipeline, &cmd_line);
	g_status = ft_set_env(&all, &env, envp);
	if (g_status != 0)
		return (ft_dprintf(2, "Memory allocation failed\n"), 2);
	g_status = readline_loop(&all, &cmd_line);
	if (g_status == -2 || g_status == 254)
	{
		ft_dprintf(2, "Memory allocation failed\n");
		free_all(&all);
	}
	return (g_status);
}
