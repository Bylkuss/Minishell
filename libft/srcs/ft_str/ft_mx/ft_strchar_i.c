/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:11:39 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/08 11:21:52 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
