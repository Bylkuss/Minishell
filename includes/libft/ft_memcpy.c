/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:04:50 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/23 18:20:23 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src1;

	dest = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	i = 0;
	if (!dest && !src1)
		return (NULL);
	while (i < n)
	{
		dest[i] = src1[i];
		i++;
	}
	return ((void *)dest);
}

/*
int	main(void)
{
	int	dest[50 ]= {4, 3, 2, 1};
	int	src[50]= {1, 2, 3, 4};
    ft_memcpy(dest, src, 4);
    printf("%d", dest[3]);
}
*/