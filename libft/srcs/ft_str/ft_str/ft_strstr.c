/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:42:17 by gehebert          #+#    #+#             */
/*   Updated: 2021/09/16 13:28:05 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<string.h>
#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	if (to_find[pos] == '\0')
		return (str);
	while (str[i] != '\0' && to_find[pos] != '\0')
	{
		if (to_find[pos] == str[i])
		{
			while (str[i + pos] == to_find[pos] && to_find[pos] != '\0')
				pos ++;
		}
		if (to_find[pos] == '\0')
			return (&str[i]);
		i ++;
		pos = 0;
	}
	return (0);
}
