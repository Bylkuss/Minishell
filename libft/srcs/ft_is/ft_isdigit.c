/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 09:06:14 by gehebert          #+#    #+#             */
/*   Updated: 2021/09/14 09:29:26 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
//ft_isdigit  by germ
//

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}