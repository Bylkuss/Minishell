/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:03:35 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/14 23:56:57 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_vcalloc(size_t count, int value)
{
	size_t	i;
	int		*mem;

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
