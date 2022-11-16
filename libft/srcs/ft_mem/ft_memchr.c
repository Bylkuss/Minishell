/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 08:24:07 by gehebert          #+#    #+#             */
/*   Updated: 2021/09/17 06:13:15 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr;
	size_t		i;

	ptr = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (char)c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
