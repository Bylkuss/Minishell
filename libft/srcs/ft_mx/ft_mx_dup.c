/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:34:46 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/15 10:24:02 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	**ft_mx_dup(char **mx)
{
	char	**tab;
	int		n_itm;
	int		i;

	i = 0;
	n_itm = ft_mx_len(mx);
	tab = malloc(sizeof(char *) * (n_itm + 1));
	if (!tab)
		return (NULL);
	while (mx[i])
	{
		tab[i] = ft_strdup(mx[i]);
		if (!tab[i])
		{
			ft_mx_free(&tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
