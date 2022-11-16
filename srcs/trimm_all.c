/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimm_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:28:33 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/15 23:27:50 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


static int  malloc_len(const char *s)
{
    int count;
    int i;
    int dquote;
    int squote;

    i = 0;
    count = 0;
    dquote = 0;
    squote = 0;
    while (s)
    {
        squote = (squote + (!dquote && s[i] == '\'')) % 2;
        dquote = (dquote + (!squote && s[i] == '\"')) % 2; 
        if ((s[i] == '\"' && !squote) || (s[i] == '\'' && !dquote)) 
            count++;
    }
    if (squote || dquote)
        return (-1);
    return (count);
}

char        *ft_strtrim_all(const char *s, int squote, int dquote)
{
    int     count;
    int     i[2];
    char    *trimmed;

    i[1] = -1;
    i[0] = 0;
    count = malloc_len(s);
    if (!s || count == -1)
        return (NULL);
    trimmed = malloc(sizeof(char) * (ft_strlen(s) - count + 1));
    if (!trimmed)
        return (NULL);
    while( s[i[0]])
    {
        squote = (squote + (!dquote && s[i[0]] == '\'')) % 2;
        dquote = (dquote + (!squote && s[i[0]] == '\"')) % 2; 
        if ((s[i[0]] != '\"' || squote) && (s[i[0]] != '\'' || dquote) \
            && ++i[1] >= 0)
            trimmed[i[1]] = s[i[0]]; 
        i[0]++;
    }
    trimmed[++i[1]] = '\0';
    return (trimmed);
}
