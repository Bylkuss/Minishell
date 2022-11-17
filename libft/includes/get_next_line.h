/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:49:36 by gehebert          #+#    #+#             */
/*   Updated: 2021/11/02 08:28:17 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char 	*ft_read(int fd);   //, char *line);
int		ft_find(char *str);
char    *ft_get_set(char *line);
char    *ft_saved(char *line);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t n);

#endif