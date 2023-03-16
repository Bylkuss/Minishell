/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:35:15 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/15 10:37:03 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	un_c;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	un_c = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == un_c)
			return (i);
		i++;
	}
	if (un_c == '\0')
		return (i);
	return (-1);
}
