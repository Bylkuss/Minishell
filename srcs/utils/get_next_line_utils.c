/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:36:16 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/17 14:03:08 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t	gnl_strlen(char const *str)
{
	int	num;

	num = 0;
	if (!str)
		return (0);
	while (str[num] != '\0')
		num++;
	return (num);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	lens;
	size_t	i;

	if (!s)
		return (NULL);
	lens = gnl_strlen(s);
	i = 0;
	if (len >= lens)
		len = lens;
	if (start >= lens)
	{
		res = (char *)malloc(1);
		if (res == NULL)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (i++ < start)
		s++;
	gnl_strlcpy(res, s, len + 1);
	return (res);
}

size_t	gnl_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;
	size_t			sz;

	i = 0;
	if (src == NULL)
		return (0);
	sz = gnl_strlen(src);
	if ((int)n < 0)
		n = sz + 1;
	if (n >= 2 && sz != 0)
	{
		while (i < n - 1)
		{
			if (i < sz)
				dest[i] = src[i];
			else if (i == sz)
				dest[i] = '\0';
			i++;
		}
	}
	if (n != 0)
		dest[i] = '\0';
	return (sz);

}

size_t	gnl_strlcat(char *dst, const char *src, size_t size)
{
	char			*ptr;
	unsigned int	i;

	if (size < gnl_strlen(dst))
		return (gnl_strlen(src) + size);
	ptr = dst + gnl_strlen(dst);
	i = gnl_strlen(dst);
	while (i < size - 1 && *src != '\0' && size >= 2)
	{
		*ptr = *src;
		ptr++;
		src++;
		i++;
	}
	if (size != 0)
		*ptr = '\0';
	return (gnl_strlen(dst) + gnl_strlen(src));
}

int gnl_strchr_i(const char *s, int c)
{
    unsigned char   un_c;
    int             i;

    i = 0;
    if (!s)
        return (-1);
    un_c = (unsigned char)c;
    while (s[i] != '\0')
    {
        if (s[i] == un_c)
            return (i);
        i++;
    }
    if (un_c == '\0')
        return (i);
    return (-1); 
}