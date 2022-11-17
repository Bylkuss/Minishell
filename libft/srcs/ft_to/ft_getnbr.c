/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:15:47 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:15:49 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	ft_getnbr(char const *str)
{
	int		nbr;
	int		neg;

	nbr = 0;
	neg = 0;
	if (*str == '-')
	{
		str++;
		neg++;
	}
	while (*str)
	{
		nbr *= 10;
		nbr = (*str - 48) + nbr;
		str++;
	}
	if (neg)
		nbr *= -1;
	return (nbr);
}
