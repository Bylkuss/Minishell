/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:15:57 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/04 14:34:51 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ischar(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
		if (*(set + i++) == c)
			return (1);
	return (0);
}

static char	*trimming(const char *s1, const char *set, size_t *k, size_t i)
{
	size_t	j;
	size_t	len;
	char	*dst;

	len = ft_strlen(s1);
	j = 0;
	while (ischar(*(s1 + len - j - 1), set))
		j++;
	dst = ft_calloc(sizeof(char), len - (j + i) + 1);
	if (dst == NULL)
		return (NULL);
	while (*k < len - (j + i))
	{
		*(dst + *k) = *(s1 + i + *k);
		*k += 1;
	}
	return (dst);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	k;
	size_t	len;
	char	*dst;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (ischar(*(s1 + i), set))
		i++;
	k = 0;
	if (i == len)
		dst = malloc(1);
	else
		dst = trimming(s1, set, &k, i);
	if (dst != NULL)
		*(dst + k) = '\0';
	return (dst);
}
