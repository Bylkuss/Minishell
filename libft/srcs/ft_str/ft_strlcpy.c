/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:20:52 by gehebert          #+#    #+#             */
/*   Updated: 2021/09/30 10:47:08 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;
	size_t			sz;

	i = 0;
	if (src == NULL)
		return (0);
	sz = ft_strlen(src);
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
