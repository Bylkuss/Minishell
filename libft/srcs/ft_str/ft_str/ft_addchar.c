/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:21:41 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:21:44 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_addchar(char *str, char c)
{
	char		*res;
	int			len;
	int			i;

	i = -1;
	len = ft_strlen(str);
	res = ft_calloc(len + 2, sizeof(char));
	while (++i < len)
		res[i] = str[i];
	res[i] = c;
	free(str);
	return (res);
}
