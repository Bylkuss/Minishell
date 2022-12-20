/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_rpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:34:29 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/06 12:34:42 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char **ft_mx_rpl(char ***full, char **tab, int n)
{
    char **tmp;
    int i[3];

    i[0] = -1;
    i[1] = -1;
    i[2] = -1;
    if (!full || n < 0 || n >= ft_mx_len(*full))
        return (NULL);
    tmp = ft_calloc(ft_mx_len(*full) + ft_mx_len(tab), sizeof(char *));
    while(tab &&full[0][++i[0]])
    {
        if (i[0] != n)
            tmp[++i[2]] = ft_strdup(full[0][i[0]]);
        else
        {
            while (tab && tab[++i[1]])
                tmp[++i[2]] = ft_strdup(tab[i[1]]);
        }
    }
    ft_mx_free(full);
    *full = tmp;
    return (*full);
}