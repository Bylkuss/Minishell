/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:06:39 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:06:42 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}
