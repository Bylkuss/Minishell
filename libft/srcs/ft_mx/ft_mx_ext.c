/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:34:18 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/06 12:34:21 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../incs/libft.h"

char **ft_mx_ext(char **stk, char *str)
{
    char **tab;
    int len;
    int i;

    i = -1;
    tab = NULL;
    if (!str)
        return (stk);   
    len = ft_mx_len(stk);
    tab = malloc(sizeof(char *) * (len + 2));
    tab[len + 1] = NULL;
    if (!tab)
        return (stk);
    while(++i < len)
    {
        tab[i] = ft_strdup(stk[i]);
        if (!tab[i])
        {
            ft_mx_free(&stk);
            ft_mx_free(&tab);
        }
    }
    tab[i] = ft_strdup(str);
    ft_mx_free(&stk);
    return (tab);
}