/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:43:12 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/07 10:28:40 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lenght;
	char	*str;

	if (!s)
		return (NULL);
	lenght = ft_strlen(s);
	if (len > lenght)
		len = lenght;
	str = ft_calloc(sizeof(char), len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start < lenght && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
