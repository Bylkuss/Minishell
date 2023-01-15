/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_unx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:34:57 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/15 02:51:24 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char *ft_mx_unx(char *full, char **tab, int len)
{
    // char **tab;
    // int l;
    int i;

    i = -1;
    tab = NULL;
    if (!tab)
        return (full);   
    if (!len)
    len = ft_mx_len(tab);
        // tab = malloc(sizeof(char *) * (len + 2));
        // tab[len + 1] = NULL;
        // if (!tab)
        //     return (stk);
    while(++i < len)
    {
        full = ft_strjoin(full, tab[i]);
        if (++i < len)
        {
            full = ft_strjoin(full, " ");
            i--;
            
            // ft_mx_free(&stk);
            // ft_mx_free(&tab);
        }
    }
    //  = ft_strdup(str);
    ft_mx_free(&tab);
    return (full);
}