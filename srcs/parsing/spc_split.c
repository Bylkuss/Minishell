/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:05:13 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/17 13:36:50 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int node_count(const char *s, char *c, int i[2]) // 
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
                    if(!q[1] && (s[i[0]] == '\"' || s[i[0]] != '\0')) 
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

/*
    Space_Split_Form_           "..." "..." "..."
*/

static char **node_fill(char **arr, const char *s, char *set, int i[3]) 
{
        int     len;
        int     q[2];       // uniq_quotes ignore

        q[0] = 0;
        q[1] = 0;
        len = ft_strlen(s);
        while (s[i[0]])
        {
            while(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')   // set = space
                i[0]++;
            i[1] = i[0];
            while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) & s[i[0]])
            {
                q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;     //single_ignore
                q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;     //single_ignore
                i[0]++;
            }
            if (i[1] >= len)
                arr[i[2]++] = "\0";
            else
                arr[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);  //
        }
        return (arr);
}

/*
    cmd space_trim :: token_part   
*/
char **space_split(const char *s, char *set)
{
        char    **arr;
        int     nodes;
        int     i[3];       // *arr pos: start, sub-end, end
        int     count[2];   // str sub len [0:start/1:end]

        i[0] = 0;
        i[1] = 0;
        i[2] = 0;
        count[0] = 0;
        count[1] = 0;
        if (!s)
            return (NULL);
        nodes = node_count(s, set, count);     // node = str.space.cut 
        if (nodes == -1)
            return (NULL);
        // tab
        printf(":: %d  NODES ::\n",nodes);
        arr = (char **)malloc(sizeof(char *) * (nodes + 1)); //strc malloc
        if (arr == NULL)
            return (NULL);

        arr = node_fill(arr, s, set, i);    // null-term str return
        // mx_display_tab(arr);                // arr[nodes] = NULL;
        return (arr);   
}

/*
from parse.c
    space_split => split *str by space only (quote rule (ok if both))
    word_count + ft_fill_node ... ... seems legit!
    *** space_split: trunk at space to make token part
*/