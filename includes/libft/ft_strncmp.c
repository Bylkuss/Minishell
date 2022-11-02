/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:51:41 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/23 18:50:31 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (diff);
}
/*
int	main(void)
{
	printf("ft_strncmp:: %d \n", ft_strncmp("vgchgjd", "dfgjddghj", 9));
	printf("   strncmp:: %i \n", strncmp("vgchgjd", "dfgjddghj", 9));
	return (0);
}
*/