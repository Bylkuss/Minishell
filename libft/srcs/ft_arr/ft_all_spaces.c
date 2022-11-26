/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:20:59 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:21:01 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_all_spaces(char *str)
{
	int			i;
	int			j;

	i = -1;
	j = ft_strlen(str);
	while ((++i < j) && (ft_isspace_nl(str[i]) && str[i] != '\n'))
		;
	if (i == j)
		return (1);
	else
		return (0);
}
