/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_split.c                                         :+:      :+:    :+:   */
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
        if (!ft_strchr(c, s[i[0]])) // value -0- at pos [i] into *s
        {
            while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
            {
                if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\'')) 
                    q[1] = s[i[0]];
                q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
                q[1] *= q[0] != 0;
                i[0]++;
            }
            if (q[0])
                return (-1);
        }
        else if (ft_strchr(c, s[i[0]])) 
        {
            while (ft_strchr(c, s[i[0]]))
                i[0]++;
            i[1]++;
        }
    }
    return (i[1] + 1);
}

/*   init_split_Form_           "..." "..." "..." */
static char **node_fill(t_table *tab, const char *s, char *set, int i[3]) 
{
    int     n;      //node id
    int     len;
    int     q[2];       // uniq_quotes ignore

    n = 0;
    q[0] = 0;
    q[1] = 0;
    len = ft_strlen(s);
    printf("DEBUG: node_fill  :: len = %d \n", len);        // strlen
    i[2] = -1;
    while (s[i[0]] && i[0] < len)
    {
        if(!ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')                      // spc found
        {
            i[2] = i[0];
            while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
            {
                // printf("DEBUG: n_fill -- i[2] = [%d][%d][%c]\n", n, i[0], s[i[0]]);     // NOT
                q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;     //single_ignore
                q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;     //single_ignore
                i[0]++;
            }
        }
        if(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')                      // spc found
        {
            i[1] = i[0]++;    // set spc - end of str...
            while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
                i[0]++;
        }
        if (i[0] <= len && i[2] > -1)
        {
            tab->node[n] = ft_substr((char *)s, i[2], (i[1] - i[2])); 
            // printf("DEBUG:  node[%d]_\n", n);
            tab->node = ft_mx_ext(tab->node, tab->node[n]);
            printf("node[%d] => ::%s::\n", n, tab->node[n]);
            n++;
        }            
        if(i[0] == len)
            tab->node = ft_mx_ext(tab->node, "@");
        // printf("node[%d] => ::%s::\n", n, tab->node[n]);
    }
    // mx_display_tab(tab->node);
    return (tab->node);
}

//    ls -lat |head -2|wc -l> out.txt   
char **init_split(const char *s, char *set, t_table *tab)
{
    int     n;
    int     i[3];       // *arr pos: start, sub-end, end
    int     count[2];   // str sub len [0:start/1:end]

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    count[0] = 0;
    count[1] = 0;
    if (!s)
        return (NULL);    
    n = node_count((const char *)s, set, count);    // substr 
    printf("DEBUG: init_split  ::  node_count = %d \n", n); 
    if (n == -1)
        return (NULL);
    tab->node = malloc(sizeof(char *) * (n + 2));   // malloc +2 EOT char
    if (!tab->node)
        return (NULL);

    tab->node = node_fill(tab, s, set, i);    // tab->cmds <<  set(" "), *s, i[] 
    return (tab->node);   // ret(tab->node)
}

/*
from parse.c
    init_split => split *str by space only (quote rule (ok if both))
    word_count + ft_fill_node ... ... seems legit!
    *** init_split: trunk at space to make token part
*/