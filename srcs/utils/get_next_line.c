/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:36:06 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/17 14:03:02 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_read(int fd)  
{
	char	*aux;
	int		red;	// val de lect. read.

	aux = malloc(BUFFER_SIZE + 1);// * sizeof(char));   // box to be fill
	if (!aux)
		return (NULL);
	red = read(fd, aux, BUFFER_SIZE);   // filling it
	if (red < 0)	//  err
	{
		free(aux);
		return (NULL);
	}
	aux[red] = '\0';
	return (aux);
		// if (!aux[0])
		// {
		// 	free (aux);
		// 	return (box);
		// }
		// if (!box)
		// 	return (aux);
		// box = ft_strdup(aux);
		// free (aux);
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
	len = ft_strlen(buf) + ft_strlen(aux);
	box = malloc(len + 1);
	if (!box)
		return (NULL);
	ft_strlcpy(box, buf, len + 1);
	ft_strlcat(box, aux, len + 1);
	free(buf);
	free(aux);
	return (box);
}

char	 *ft_set_line(char *buf, char *line) 
{
	int		i;  // index
	char	*ret;  // associated str...
	// char 	*box;	// transport var

	ret = NULL;
	if (!buf || !line)
		return(buf);
	i = ft_strlen(line);
	
	if ((int)ft_strlen(buf) == i)
	{
		free(buf);
		return (NULL);
	}
	ret = ft_substr(buf, i, ft_strlen(buf) - i);
	free(buf);
	return (ret);
}

char	*get_next_line(int fd)
{
	size_t		len;
	char		*line;
	static char *box[4096];

	if (fd < 0 || fd > 4095 || BUFFER_SIZE < 0)  // input selector
		return (NULL);
	line = NULL;
	if (ft_strchr_i(box[fd], '\n') == -1)
	{			
		len = ft_strlen(box[fd]);
		box[fd] = ft_get_input(box[fd], fd);
		if (len == ft_strlen(box[fd]) && box[fd])
			line = ft_substr(box[fd], 0, ft_strlen(box[fd]));
	}
	if (!box[fd])
		return (NULL);
	if (!line && ft_strchr_i(box[fd], '\n') != -1)
		line = ft_substr(box[fd], 0, ft_strchr_i(box[fd], '\n') + 1);
	if (line)
	{
		box[fd] = ft_set_line(box[fd], line);
		return (line); 
	}
	return (get_next_line(fd));
}