/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:03:35 by gehebert          #+#    #+#             */
/*   Updated: 2022/07/28 09:03:38 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	*ft_vcalloc(size_t count, int value)
{
	size_t		i;
	int			*mem;

	i = 0;
	mem = (int *)malloc(count * sizeof(int));
	if (!mem)
		return (NULL);
	while (i < count)
	{
		mem[i] = value;
		i++;
	}
	return (mem);
}
