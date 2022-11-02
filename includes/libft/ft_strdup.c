/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:23:41 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/23 18:02:12 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;
	size_t	len;

	i = 0;
	str = (char *)s1;
	len = ft_strlen(str);
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	*source;

	source = ". | .";
	ft_strdup(source);
	printf("%s", ft_strdup(source));
	return (0);
}
*/