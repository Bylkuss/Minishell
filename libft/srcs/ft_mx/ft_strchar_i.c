/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:35:26 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/06 12:35:30 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../incs/libft.h"

int ft_strchar_i(const char *s, char *set) 
{
    int     i;

    i = 0;
    if (!s)
        return (-1);
    while (s[i] != '\0')
    {
        if (ft_strchr(set, s[i]))
            return (i);
        i++;
    }
    return (-1);
}