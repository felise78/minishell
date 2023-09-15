/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pichatte <pichatte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:28:43 by pichatte          #+#    #+#             */
/*   Updated: 2023/09/13 15:30:09 by pichatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

typedef struct s_printf
{
	int	fd;
	int	count;	
}	t_printf;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

/*ASCII*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/*MEMORY*/
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	free_malloc(char **strs, size_t num);

/*STRINGS*/
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strchr_one(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strrchr_one(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2, int n);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
size_t	num_words(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

/*NUMBERS*/
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
int		malloc_len(int n);

/*LINKED LISTS*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list **lst, t_list *node, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*GNL*/
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char **s2);
void	ft_strcat_gnl(char *dest, char const *src);
void	ft_strcpy(char *dst, char *src, size_t n);
char	*ft_strchr_gnl(char **s, int c, int *i);
void	free_line(char **str);

/*FT_PRINTF*/
int		ft_dprintf(int fd, const char *str, ...);
void	ft_puthex_lower(unsigned int a, int fd);
void	ft_puthex_upper(unsigned int a, int fd);
void	ft_putunsigned(unsigned int i, int fd);
void	ft_putptr(unsigned long a, int fd);
int		dec_len(int n);
int		hex_len(unsigned long n);
int		unsigned_len(unsigned int n);

#endif
