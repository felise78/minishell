/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:50 by bourdon           #+#    #+#             */
/*   Updated: 2023/09/19 18:03:48 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "parsing.h"

typedef struct s_general	t_general;
typedef struct s_token		t_token;

typedef enum s_builtins
{
	b_other,
	b_echo,
	b_cd,
	b_pwd,
	b_export,
	b_unset,
	b_env,
	b_exit	
}	t_builtins;

/*ECHO*/
int			ft_echo(char **str_and_opt, int i, int n);

/*PWD*/
int			ft_pwd(char **cmd_and_args);

/*CD*/
int			ft_cd(t_general *all, char **cmd_and_args);
int			cd_errors(char **cmd_and_args);
int			cd_and_set_pwd(t_general *all, char *dir, char *original);
int			set_pwd(t_general *all, char *new_pwd);
int			del_periods(t_list **path, char **dir);
int			check_periods(char **dir);

/*ENV*/
char		*ft_getenv(t_general *all, char *var);
int			ft_env(t_general *all, char **cmd_and_args);
int			ft_export(t_general *all, char **cmd_and_args);
int			export_new_env(t_general *all);
int			sort_envp(t_general *all);
int			var_declared(t_general *all, t_token **var);
int			ft_unset(t_general *all, char **cmd_and_args);
t_list		*node_in_env(t_general *all, char *line);

/*EXIT*/
int			ft_exit(t_general *all, char **cmd_and_args);

/*OTHER*/
int			is_builtin(t_token *token);
int			dup_fds_for_builtin(t_general *all, t_token **cmdline);
int			exec_builtin(t_general *all, t_token **cmdline,
				int i, t_builtins cmd_type);
int			check_option(char **cmd_and_args);

#endif