/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:04:34 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:04:37 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	*ft_sort_nbr(int *arr, int len)
{
	int		i;
	int		j;
	int		tmp;
	int		*ret;

	ret = malloc(sizeof(int) * len);
	i = -1;
	while (++i < len)
		ret[i] = arr[i];
	i = -1;
	while (++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (ret[i] > ret[j])
			{
				tmp = ret[i];
				ret[i] = ret[j];
				ret[j] = tmp;
			}
		}
	}
	return (ret);
}
