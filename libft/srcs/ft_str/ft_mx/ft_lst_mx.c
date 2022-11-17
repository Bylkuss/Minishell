/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:24:42 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/08 11:25:26 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char **ft_lst_mx(t_list *lst)
{
    char    **mx;
    t_list  *tmp;
    char    *swp;

    tmp = lst;
    mx = NULL;
    while (tmp)
    {
        swp = ft_strdup((const char *) tmp->content);
        mx = ft_mx_ext(mx, swp);
        tmp = tmp->next;
        free(swp);
    }
    return (mx);
}
