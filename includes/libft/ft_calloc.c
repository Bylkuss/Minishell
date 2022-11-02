/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:44:48 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/25 11:02:07 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	ptr = malloc(nmemb * size);
	if (!(ptr))
		return (NULL);
	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
