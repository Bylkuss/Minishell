/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:49:36 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/14 23:27:18 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*ft_read(int fd);
char	*ft_get_input(char *buf, int fd);
char	*ft_set_line(char *buf, char *line);
char	*get_next_line(int fd);

char	*gnl_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_strlen(char const *str);
size_t	gnl_strlcpy(char *dest, const char *src, size_t n);
size_t	gnl_strlcat(char *dst, const char *src, size_t size);
int		gnl_strchr_i(const char *s, int c);

#endif