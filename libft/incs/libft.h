/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 06:55:31 by gehebert          #+#    #+#             */
/*   Updated: 2022/03/07 12:47:41 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>

# define BUFF_SIZE 32

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;
// ps
typedef struct s_dlist
{
	void			*content;
	int 			cont;
	struct s_dlist	*next;
	struct s_dlist	*prev;
	int				pos;
}					t_dlist;

//  ps
int				ps_atoi(char *s);
long long		ps_atoll(char *s);
// ft_is
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
// ft_to
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int nb);
int		ps_atoi(char *s);
//ft_mem
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t n, size_t size);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		*ft_vcalloc(size_t count, int value);
void	ft_memdel(void **ap);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memalloc(size_t size);
//ft_str
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *h, const char *n, size_t len);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *str, char c);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
// ft_lst
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *nw);
void	ft_lstadd_back(t_list **lst, t_list *nw);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);
// ft_arr
void	ft_free_arg(char **arg);
void	ft_free_array(char **array);
char	**ft_freearray(char **array);
int		*ft_sort_nbr(int *arr, int len);
void	ft_putchar(char c);
void	ft_putnbr(int n);
int		ft_iswall(int c);
int		ft_isspace(int c);
int		ft_isspace_nl(int c);
int		ft_isnbr(char *s);
int		ft_intlen(int n);
void	ft_intcpy(int *src, int *dst, int len);
int		ft_getnbr(char const *str);
char	**ft_free(char **array, int size);
int		ft_findchar(char *str, char c);
int		ft_all_spaces(char *str);
int		ft_arraylen(char **str);
int		ft_abs(float num);
// ft_mx
t_list		*ft_mx_lst(char **mx);
char		**ft_lst_mx(t_list *lst);
char		*ft_char_str(char c);
char		**ft_mx_dup(char **mx);
char		**ft_mx_ext(char **stk, char *str);
void		ft_mx_fd(char **s, int fd);
// char		*ft_mx_unx(char *full, char **tab, int len);
char		**ft_mx_rpl(char ***full, char **tab, int n);
int			ft_mx_len(char **mx);
void		ft_mx_free(char ***mx);
int			ft_strchr_i(const char *s, int c);
int			ft_strchar_i(const char *s, char *set); 
int			ft_atoi2(const char *nptr, long *nbr);

//int		split_av(char ***str, char **av, char *c);

#endif
