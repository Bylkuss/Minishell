/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:21:18 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:21:21 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_addstr(char ***arr, char *str)
{
	char		**tmp;
	int			len;
	int			i;

	len = ft_arraylen(*arr);
	tmp = malloc(sizeof(char *) * (len + 2));
	tmp[len + 1] = NULL;
	tmp[len] = str;
	i = -1;
	while (*(*arr + ++i))
		tmp[i] = *(*arr + i);
	free(*arr);
	*arr = tmp;
}
