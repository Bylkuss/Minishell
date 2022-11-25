/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:12:55 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:12:58 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	ft_isspace_nl(int c)
{
	return ((c == '\t') || (c == '\v') || (c == '\f')
		|| (c == '\r') || (c == ' '));
}

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_arespace(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}
