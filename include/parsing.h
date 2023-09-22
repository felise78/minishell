/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:49:57 by hemottu           #+#    #+#             */
/*   Updated: 2023/09/21 16:54:41 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include "../src/libft/include/libft.h"
# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_general	t_general;

typedef enum s_type
{
	WORD,
	CMD,
	ARG,
	VAR,
	PIPE,
	HEREDOC,
	REDIR_INPUT,
	REDIR_OUTPUT,
	APPEND
}	t_type;

struct s_token
{
	char		*value;
	t_type		type;
	t_token		*next;	
};

typedef struct s_var
{
	char	*value;
	char	*expand;
	int		len_var;
	int		len_exp;
}	t_var;

void	ft_analyse_words(t_token **cmd_line);
void	ft_copy_expand(t_var *var, char *str);
void	print_syntax_error(t_type type);
void	ft_check_if_token2remove(t_token **cmd_line);
void	ft_token_add_back(t_token **list, t_token *new);
void	ft_tokendelone(t_token **cmd_line, t_token *token, void (*del)(void *));
void	ft_analyse_again(t_token **cmd_line);
void	warning_eof(char *delim);
void	ft_handle_heredoc_signal(t_general *all);
void	handler_heredoc(int signum);
int		ft_check_if_heredoc(t_token **cmd_line, t_general *all);
int		analyse_delimiter(t_token **cmd_line, char *str, int i);
int		is_quote_closed(char *str);
int		ft_lexer(t_token **cmd_line, char *str, int i);
int		create_token(t_token **cmd_line, t_type type, char *str);
int		size_lexer(char *str, int i);
int		is_space(char c);
int		is_redir(char c);
int		len_until_delimiter(char *str, int i);
int		ft_check_syntax_tokens(t_token **cmd_line);
int		ft_parse4quotes(t_token **cmd_line);
int		is_var_to_expand(char *str);
int		ft_check_if_expand(t_token **cmd_line, t_general *all, t_token *current);
int		ft_len_variable(char *str, int i);
int		ft_strcmpenv(char *s1, int index, char *s2, int len);
int		ft_expand_len(t_list *in_env, t_var *var);
int		ft_strchrstr(char *str1, char *str2);
int		ft_len(int n);
int		ft_check4var(t_token *token);
int		token_word(t_token **cmd_line, char *str, int i);
int		heredoc_count(t_token *current);
int		close_heredoc_fd(int fd);
char	*ft_expand_var(char *str, int i, t_general *all, t_var *var);
char	*replace_expand(char *str, int j, t_var *var, char *expand);
char	*remove_expand(char *str, int j, t_var *var);
char	*heredoc_expand(char *buffer, t_general *all);
char	*expand_exit_code(char *str, int j, t_var *var);
t_list	*ft_is_variable_in_env(char *str, int i, t_general *all, t_var *var);
t_list	*ft_set_exit_var(t_var *var, t_list *current);
t_token	*ft_token_last(t_token *list);
t_token	*ft_token_new(char *str, t_type type);

#endif