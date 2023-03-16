/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:15:47 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/14 23:54:42 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getnbr(char const *str)
{
	int	nbr;
	int	neg;

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
