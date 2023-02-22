/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:32:34 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/21 22:32:41 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"


t_list *ft_mx_lst(char **mx)
{
    t_list *lst;
    int i;

    lst = NULL;
    i = -1;
    while (mx[++i])
        ft_lstadd_back(&lst, ft_lstnew(ft_strdup(mx[i])));
    return (lst);
}