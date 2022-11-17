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
	size_t	stot;
	char	*new;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1_len = (ft_strlen((char *) s1));
	s2_len = (ft_strlen((char *) s2));
	stot = s1_len + s2_len + 1;
	new = malloc(sizeof(char) * stot + 1);
	if (!new)
		return (NULL);
	ft_memmove(new, s1, s1_len);
	ft_memmove(new + s1_len, s2, s2_len);
	new[stot - 1] = '\0';
	return (new);
}
