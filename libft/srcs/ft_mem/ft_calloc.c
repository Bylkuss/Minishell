/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:06:20 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/01 11:15:16 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	char	*new;

	if (n <= 0 || size <= 0)
		new = (char *)malloc(1);
	else
		new = (char *)malloc(n * size);
	if (!new)
		return (NULL);
	return (ft_memset(new, 0, n * size));
}
