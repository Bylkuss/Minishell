/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:36:06 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/14 23:04:00 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_read(int fd)
{
	char	*aux;
	int		red;

	aux = malloc(BUFFER_SIZE + 1);
	if (!aux)
		return (NULL);
	red = read(fd, aux, BUFFER_SIZE);
	if (red < 0)
	{
		free(aux);
		return (NULL);
	}
	aux[red] = '\0';
	return (aux);
}

char	*ft_get_input(char *buf, int fd)
{
	char	*aux;
	char	*box;
	int		len;

	aux = ft_read(fd);
	if (!aux)
		return (NULL);
	if (!aux[0])
	{
		free(aux);
		return (buf);
	}
	if (!buf)
		return (aux);
	len = gnl_strlen(buf) + gnl_strlen(aux);
	box = malloc(len + 1);
	if (!box)
		return (NULL);
	gnl_strlcpy(box, buf, len + 1);
	gnl_strlcat(box, aux, len + 1);
	free(buf);
	free(aux);
	return (box);
}

char	*ft_set_line(char *buf, char *line)
{
	int		i;
	char	*ret;

	ret = NULL;
	if (!buf || !line)
		return (buf);
	i = gnl_strlen(line);
	if ((int)gnl_strlen(buf) == i)
	{
		free(buf);
		return (NULL);
	}
	ret = gnl_substr(buf, i, gnl_strlen(buf) - i);
	free(buf);
	return (ret);
}

char	*get_next_line(int fd)
{
	size_t		len;
	char		*line;
	static char	*box[4096];

	if (fd < 0 || fd > 4095 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	if (gnl_strchr_i(box[fd], '\n') == -1)
	{
		len = gnl_strlen(box[fd]);
		box[fd] = ft_get_input(box[fd], fd);
		if (len == gnl_strlen(box[fd]) && box[fd])
			line = gnl_substr(box[fd], 0, gnl_strlen(box[fd]));
	}
	if (!box[fd])
		return (NULL);
	if (!line && gnl_strchr_i(box[fd], '\n') != -1)
		line = gnl_substr(box[fd], 0, gnl_strchr_i(box[fd], '\n') + 1);
	if (line)
	{
		box[fd] = ft_set_line(box[fd], line);
		return (line);
	}
	return (get_next_line(fd));
}
