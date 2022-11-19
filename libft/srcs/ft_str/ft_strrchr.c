/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:35:14 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/01 12:16:40 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;
	char			*str;

	i = 0;
	str = (char *)s;
	uc = (unsigned char)c;
	while (s[i])
		i++;
	if (!c)
		return (str + i);
	i--;
	while (i >= 0)
	{
		if (uc == str[i])
			return (str + i);
		i--;
	}
	return (NULL);
}
