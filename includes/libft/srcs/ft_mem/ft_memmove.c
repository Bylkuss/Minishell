/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:25:13 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/07 10:28:40 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*src1;

	dest = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (!dest && !src1)
		return (NULL);
	if (src1 < dest)
		while (len--)
			dest[len] = src1[len];
	else
		while (len--)
			*(dest++) = *(src1++);
	return (dst);
}
