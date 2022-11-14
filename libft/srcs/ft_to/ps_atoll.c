/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:08:54 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/13 23:09:33 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

long long	ps_atoll(char *s)
{
	int					i;
	int					neg;
	unsigned long long	ret;

	i = 0;
	ret = 0;
	neg = 1;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\v' || \
		s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-')
		neg = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = 10 * ret + s[i] - '0';
		i++;
	}
	ret = ret * neg;
	return (ret);
}