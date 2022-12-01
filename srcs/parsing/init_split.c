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


//  set dbl pipe
//      spc-bef / spc-aft
//

char *pipe_check(char *input, char *meta)
{
    char *tmp;
    char *dest;
    int i[2];
  
    i[1] = 1;
    i[0] = ft_strchr_i((char *)input, *meta);
    if (i[0] && (input[i[0]+ 1]) == 124) 
        i[1] = 2;
    if (i[0] && (input[i[0] - 1]) != 32) 
    {
        tmp = ft_substr((const char *)input, 0, (ft_strlen(input) - (i[0]) - i[1]));
        dest = ft_substr((const char *)input, i[0], (ft_strlen(input) - (i[0] - i[1])));
        tmp = ft_strjoin(tmp, " ");
        input = ft_strjoin(tmp, dest);
        // printf("DEBUG  :i - 1 != 32_check :: %s \n", input);
    }
    if ((input[i[0]+ 1]) != 32)
    {
        tmp =  ft_substr((const char *)input, 0, (ft_strlen(input) - (i[0]-1)));
        dest = ft_substr((const char *)input, i[0] + i[1], (ft_strlen(input) - (i[0])));
        tmp = ft_strjoin(tmp, " ");
        input = ft_strjoin(tmp, dest);
        // printf("DEBUG  :i + 1 != 32_check :: %s \n", input);
    }
    input = ft_strjoin(tmp, dest);
    free(tmp);
    free(dest);
    return(input);
}

static int node_count(const char *s, char *c, int i[2]) // 
{
        int     q[2];   // quotes match delimter

        q[0] = 0;
        q[1] = 0;
        while (s[i[0]] != '\0')
        {
            if (!ft_strchr(c, s[i[0]])) // value -0- at pos [i] into *s
            {
                i[1]++;
                while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0') // != '," % 2
                {
                    if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\'')) 
                        q[1] = s[i[0]];
                    q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
                    q[1] *= q[0] != 0;
                    i[0]++;
                }
                if (q[0])
                    return (-1);
                // if (ft_strchr(c, s[i[0]])) 
                //     i[1]++;
            }
            else
                i[0]++;
        }
        return (i[1]);
}

/*   init_split_Form_           "..." "..." "..." */
static char **node_fill(char **arr, const char *s, char *set, int i[3]) 
{
        int     len;
        int     q[2];       // uniq_quotes ignore

        q[0] = 0;
        q[1] = 0;
        len = ft_strlen(s);
        // printf("\n::NODE_FILL_ BEGIN ::len =%d", len);      // DEBUG
        while (s[i[0]])// && i[0] <= len)
        {
            if(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')   // set = space
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
                arr[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);  
            i[0]++;
        }
            // printf("\n::NODE_FILL_ INNER:: %d", i[0]);      // DEBUG
            // // mx_display_tab(arr);
            // printf("DEBUG: arr[0] >>:: %s ::\n", arr[0]);
            // printf("::NODE_FILL_ END \n");      // DEBUG
                // printf("DEBUG: NODE >> len[%d]:: %s ::\n", len, s);
        return (arr);
}

/*    (old spc_split) readline input _init_split_  NODE MAKER   */
char **init_split(const char *s, char *set)
{
    char    **arr;
    char    *input;
    int     nodes;
    int     i[3];       // *arr pos: start, sub-end, end
    int     count[2];   // str sub len [0:start/1:end]

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    count[0] = 0;
    count[1] = 0;
    arr = NULL;
    printf("\nOK TEST INPUT!S_S BEGIN\n");      // DEBUG
        // node_chk >> insert space in before/after it if needed
        //  input divided by space ::  error if no-space-too
    if (s)
        input = pipe_check((char *)s, "|");
    else
        return (NULL);
    printf("DEBUG  :pass_to_init :: %s \n", input);
        // arr = ft_mx_ext(arr, (char *)s);    // start arr w/ empty
                    // arr[0] = node_check((char *)s, ">|<"); // dbl / smpl 've to be check
                    // insert spc. where it needs watch for dbl..
    nodes = node_count((const char *)input, set, count);     // substr 
    if (nodes == -1)
        return (NULL);
    printf("DEBUG ::: %d nodes :: spc_split end \n", nodes);      // DEBUG
    arr = malloc(sizeof(char *) * (nodes + 1)); //strc malloc
    if (!arr)
        return (NULL);
    arr = node_fill(arr, input, set, i);    // tab->cmds <<  set(" "), *s, i[] 
    arr[nodes] = NULL;
    // printf("DEBUG: init_split end!\n");
    return (arr);   // ret(tab->node)
}

/*
from parse.c
    init_split => split *str by space only (quote rule (ok if both))
    word_count + ft_fill_node ... ... seems legit!
    *** init_split: trunk at space to make token part
*/