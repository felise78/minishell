/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:31:47 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/14 18:53:06 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <termios.h>
# include <signal.h>
# include "../src/libft/include/libft.h"
# include "parsing.h"
# include "builtins.h"

extern int					g_status;

typedef struct s_pipe		t_pipe;
typedef struct s_command	t_command;

typedef struct s_general
{
	t_list		**env;
	char		**new_env;
	char		***address_envp;
	t_command	*all_cmds;
	t_pipe		*pipeline;
	t_token		**cmdline;
}	t_general;

typedef struct s_pipe
{
	int			pipes;
	int			fd[2];
	int			prev_pipe;
	__pid_t		*pid;
	t_general	*all;
	t_token		**cmdline;
}	t_pipe;

typedef struct s_command
{
	char	**cmd_args;
	t_token	*redirections;
	int		here_fd[2];
}	t_command;

/*INITS*/
void	set_pointers(t_general *all, t_pipe *pipeline, t_token **cmd_line);
int		ft_set_env(t_general *all, t_list **env, char **envp);
int		ft_init_pipes(t_general *all, t_token **cmd_line);
int		env_init(char **envp, t_list **env);

/*REDIRECTIONS*/
int		ft_dup(t_pipe *pipeline, int cmd_index);
int		ft_set_redirection(t_command *cmd);
int		is_last_heredoc(t_token **here_node);
int		close_other_heredocs(t_general *all, int i);
int		open_fd(t_command *cmd, t_token **tmp, int *fd);
int		ft_dup_redir(t_token **tmp, int *fd);
int		set_redir_lists(t_token **add_to, t_token *new_node);

/*PIPES*/
int		pipe_count(t_token **cmd_line);
int		exec_pipes(t_general *all, t_token **cmdline);
void	ft_wait(t_general *all);
int		ft_parent(t_pipe *pipeline, int i);

/*EXEC*/
int		parsing_result(char *str, t_token **cmd_line);
int		parse_cmdline(t_general *all, t_token **cmdline);
t_token	*locate_cmd(t_token **cmd_line);
int		ft_fork(t_general *all, t_token **cmd_line);
int		fork_single_command(t_general *all, t_token **cmdline);
int		check_absolute_path(t_general *all, int i);
int		ft_isdir(char *pathname);
int		find_path(t_general *all, int i);
int		join_to_path(t_general *all, int i, char **directories);
int		join_to_path_2(char *cmd, char **slash, char **directories, int j);
int		ft_exec(t_general *all, t_token **cmdline, int i);

/*UTILS*/
int		find_array_size(char **array);
char	**copy_tab(char **tab);
int		join_dir(t_list **path, char **dir);
int		set_struct_redir(char **struct_str, char *file);

/*SIGNALS*/
void	ft_signals_parent(void);
void	ft_signals_child(void);
int		handle_eof(t_general *all);
void	child_handler(int signum);
void	handler(int signum);

/*FREES*/
void	free_and_set_null(t_general *all);
void	free_tab(char ***tab);
void	free_cmds(t_general *all);
void	free_all(t_general *all);
void	ft_free_cmd_line(t_token **cmd_line);
void	use_free(void *content);

/*ERRORS*/
int		exit_in_child(t_general *all, int code);
int		check_and_close_heredoc(t_general *all, int i);
int		perror_return(char *message, int code);

#endif
