/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:37:47 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/20 13:23:06 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	deb;
	size_t	fin;

	if (!set || !s1)
		return (NULL);
	deb = 0;
	fin = ft_strlen(s1);
	while (s1[deb] && ft_strchr(set, s1[deb]))
		deb++;
	while (s1[fin - 1] && ft_strchr(set, s1[fin - 1]) && fin > deb)
		fin--;
	str = (char *)malloc(sizeof(char) * (fin - deb) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[deb], fin - deb + 1);
	return (str);
}

/*
int	main(void)
{
	char const	*set;

	set = "21";
	printf("%s\n", ft_strtrim("121ay idurar n gerger1111121111", set));
}
*/