/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 06:10:42 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/01 07:09:34 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*new;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = (char *)malloc(s1_len + s2_len + 1);
	if (new == NULL)
		return (NULL);
	while (i < s1_len || i < s2_len)
	{
		if (i < s1_len)
			new[i] = s1[i];
		if (i < s2_len)
			new[i + s1_len] = s2[i];
		i++;
	}
	new[s1_len + s2_len] = '\0';
	return (new);
}
