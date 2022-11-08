/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 09:30:42 by gehebert          #+#    #+#             */
/*   Updated: 2021/09/16 13:55:31 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*n == '\0' || n == NULL)
		return ((char *) h);
	while (h[i] != '\0' && i < len)
	{
		j = 0;
		while (n[j] == h[i + j] && i + j < len)
		{
			if (n[j + 1] == '\0')
				return ((char *) h + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
