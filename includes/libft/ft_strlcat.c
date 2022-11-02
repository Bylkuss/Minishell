/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:15:59 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/23 19:31:40 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	if (dstsize == 0)
		return (src_len);
	if (dstsize < i)
		return (src_len + dstsize);
	j = 0;
	while (src[j] && i < (dstsize - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
/*
#include <string.h>
int	main(void)
{
	char	dest[50];
	char	*src;

	dest[50] = "Azul ";
    src = "fell-awen";
    // printf("function return: %lu\n", strlcat(dest, src, 0));
    printf("my function return: %lu\n", ft_strlcat(dest, src, 10));
	printf("   function return: %lu\n", strlcat(dest, src, 10));
    // ft_strlcat(dest, src, 15);
    // printf("%s", dest);
}
*/