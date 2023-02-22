/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 06:09:02 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/08 12:12:38 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	num;

	num = 0;
	if (!str)
		return (num);
	while (*str != '\0')
	{
		num ++;
		str++;
	}
	return (num);
}
