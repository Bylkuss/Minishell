/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:30:08 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/07 10:28:40 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str || c == '\0')
	{
		if (*(str++) == (char)c)
			return (--str);
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*p2;
	char	*p1;

	p2 = "1";
	p1 = "2";
	if (p1 > p2)
	{
		printf("P1 is greater than p2");
	}
	else if (p1 == p2)
	{
		printf("P1 equals p2");
	}
	else
	{
		printf("P2 is greater than p1");
	}
	return (0);
}
*/