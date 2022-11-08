/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:11:29 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/08 11:21:07 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
