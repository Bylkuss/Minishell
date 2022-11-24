/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:11:45 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/08 11:21:34 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

int ft_strchr_i(const char *s, int c)
{
    unsigned char   un_c;
    int             i;

    i = 0;
    if (!s)
        return (-1);
    un_c = (unsigned char)c;
    while (s[i] != '\0')
    {
        if (s[i] == un_c)
            return (i);
        i++;
    }
    if (un_c == '\0')
        return (i);
    return (-1); 
}
