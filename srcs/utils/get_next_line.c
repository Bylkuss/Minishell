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

char	*ft_read(int fd)  // , char *line) // remove in transition
{
	char	 *buff;
	char	*box; //conteneur de retour
	int		ret;	// val de lect. read.

	ret = 1;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));   // box to be fill
	if (!buff)
		return (NULL);
	ret = read(fd, buff, BUFFER_SIZE);   // filling it
	if (ret == -1)	//  err
	{
		free(buff);
		return (NULL);
	}
	if (ret == 0)
	{
		free (buff);
		return (NULL);
	}
	buff[ret] = '\0';
	box = ft_strdup(buff);
	free (buff);
	return (box);
}

int		ft_find(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	 *ft_get_set(char *line) // get the first line incl \n
{
	int		i;  // index
	char	*rtn;  // associated str...
	char 	*box;	// transport var
	
	i = 0;
	rtn = NULL;
	if (!line)
		return (0);
	if (line[i] == '\n')
	{
		rtn = malloc(sizeof(char) * 1);
		rtn[i] = line[i];
		box = ft_strdup((const char *) rtn);
		free (rtn);
		return (box);
	}
	while (line[i] && line[i] != '\n')
		i++;
	// end of file to be 
	rtn = malloc(sizeof(char) * (i + 2));
	if (!rtn)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		rtn[i] = line[i];
		i++;
	}
	rtn[i] = line[i];  // incl.  '\n'
	if(line[i] == '\n')
		rtn[i + 1] = '\0';
	box = ft_strdup((const char *) rtn);	// null-terminated str to be transp
	free (rtn);		//rtn[i++] = '\0';
	return (box);
}

char	 *ft_saved(char *line) // get the first line incl \n
{
	int		i;  // index
	unsigned int 	j;	//passed index
	size_t 	k;	//len
	// char	*rtn;  // associated str...
	char 	*box;	// transport var

	// rtn = NULL;	
	i = ft_find(line);
	j = i + 1;
	while (line[i] != '\0')
		i++;
	k = (i - j);
	box = ft_substr((const char *) line, j, k);	// null-terminated str to be transp
	return (box);
}

char	*get_next_line(int fd)
{
	char	*str;
	char	*box;
	static char *line = NULL;

	str = NULL;
	box = NULL;
	if (!(fd >= 0 && fd < 6) || BUFFER_SIZE <= 0)  // input selector
		return (NULL);
	while (ft_find(line) == -1)
	{			
		box = ft_read(fd); // , line);	// get index set to line // safety checked
		if (box == NULL)
			return (NULL);
		line = ft_strjoin((const char *) line, (const char *) box); // set  into JOIN	
	}
	str = ft_get_set(line); // set str	
	if ((ft_find(line) + 1) == '\0')
	{
		free (line);
		return (NULL); 
	}
	if ((line) > (str))	
	{
		 box = ft_saved(line);
		 line = ft_strdup(box);	
	}
	line = ft_saved(line);
	//free (box);
	//free (line);
	return (str);
}