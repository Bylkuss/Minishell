/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:05:13 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/15 22:18:49 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int word_count(const char *s, char *c, int i[2])
{
    int     q[2];   // quotes match delimter

    q[0] = 0;
    q[1] = 0;
    while (s[i[0]] != '\0')
    {
        if (!ft_strchr(c, s[i[0]]))
        {
            i[1]++;
            while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
            {
                if(!q[1] && (s[i[0]] == '\"' || s[i[0]] != '\0')) //"
                    q[1] = s[i[0]];
                q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
                q[1] *= q[0] != 0;
                i[0]++;
            }
            if (q[0])
                return (-1);
        }
        else
            i[0]++;
    }
    return (i[1]);
}

static char **ft_fill_array(char **aux, const char *s, char *set, int i[3])
{
    int     len;
    int     q[2];       // quotes match

    q[0] = 0;
    q[1] = 0;
    len = ft_strlen(s);
    while (s[i[0]])
    {
        while(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
            i[0]++;
        i[1] = i[0];
        while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) & s[i[0]])
        {
            q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
            q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2; //"
            i[0]++;
        }
        if (i[1] >= len)
            aux[i[2]++] = "\0";
        else
            aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
    }
    return (aux);
}

char **ft_cmdtrim(const char *s, char *set)
{
    char    **aux;
    int     nwords;
    int     i[3];       //state pos: start, sub-end, end
    int     count[2];   // str sub len [0:start/1:end]

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    count[0] = 0;
    count[1] = 0;
    if (!s)
        return (NULL);
    nwords = word_count(s, set, count);
    if (nwords == -1)
        return (NULL);
    printf(": %d :",nwords);
    aux = malloc(sizeof(char *) * (nwords + 1));
    if (aux == NULL)
        return (NULL);
    aux = ft_fill_array(aux, s, set, i);
    aux[nwords] = NULL;
    return (aux);   
}
