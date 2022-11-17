/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:21:57 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:21:59 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(float num)
{
	int	dummy;

	dummy = (int)num;
	if ((num - dummy) >= 0.5)
		return ((int) num + 1);
	else
		return ((int) num);
}
