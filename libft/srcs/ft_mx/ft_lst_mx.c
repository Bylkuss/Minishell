/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:31:29 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/21 22:31:53 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../incs/libft.h"

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