/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:12:25 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/18 13:18:56 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	lens;
	size_t	i;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	i = 0;
	if (len >= lens)
		len = lens;
	if (start >= lens)
		return "\0";
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (i++ < start)
		s++;
	ft_strlcpy(res, s, len + 1);
	return (res);
}
