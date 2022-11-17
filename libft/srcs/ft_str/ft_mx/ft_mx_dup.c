/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:11:04 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/08 11:20:42 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char **ft_mx_dup(char **mx)
{
    char    **tab;
    int     n_itm;
    int     i;

    i = 0;
    n_itm = ft_mx_len(mx);
    tab = malloc(sizeof(char *) * (n_itm + 1));
    if (!tab)
        return (NULL);
    while(mx[i])
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
