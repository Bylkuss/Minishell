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

char *type_check(char *input, char *meta)
{
    char *srcs; //  start part str
    char *dest; //  end part str
    char *rest;  //  sub str
    int p[4];   //ptr pos start/pos/end   

    p[1] = 0;
    rest = "\0";
    srcs = ft_strdup(input);    
    while (ft_strlen(srcs) > 1 && p[1] != -1) 
    {
        p[1] = ft_strchar_i(srcs, meta);
        if (p[1] == -1)
            break;//padd = 1;
        p[3] = ft_strlen(srcs);      
        if ((p[1]) && (input[p[1] - 1] != 32) )
        {
            // printf("DEBUG ::AV_\n");
            dest = ft_substr(srcs, 0, p[1]); //bfore endtype        
            dest = ft_strjoin(dest, " ");
            rest = ft_strjoin(rest, dest);
            // printf("DEBUG ::AV_ rest_check[%ld] ::%s: \n",ft_strlen(rest), rest);
            srcs = ft_substr(srcs, p[1] , p[3] - p[1]); // left          
            // printf("DEBUG ::AV_ new_src_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);
        }    
        else if ((input[p[1] + 1] != 32) && (p[1] + 1 != p[1]))
        {
            // printf("DEBUG ::AP_\n");
            p[2] = p[1] + 1;
            if ((srcs[p[1] + 1]) == (srcs[p[1]]))   // twin chk ! 
                p[2] = p[1] + 2;
            dest = ft_substr(srcs, 0, p[2]); //bfore endtype        
            dest = ft_strjoin(dest, " ");
            rest = ft_strjoin(rest, dest); 
            // printf("DEBUG ::AP_ rest_check[%ld] ::%s: \n",ft_strlen(rest), rest);
            srcs = ft_substr(srcs, p[2], p[3] - (p[2])); // left          
            // printf("DEBUG ::AP_ new_src_check[%ld] ::%s: \n",ft_strlen(srcs), srcs); 
        }   
        else
            break;     
    }
    rest = ft_strjoin(rest, srcs);         // input = dest; 
    input = ft_strdup(rest);         // input = dest;
    printf("DEBUG ::NEW_ input_check[%ld] ::%s: \n",ft_strlen(input), input);
    return(input);
}

static int token_count(const char *s, char *c, int i[2]) // 
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
    // printf("DEBUG: token_count: (n = %d)\n", i[1]);
    return (i[1] );//+ 1); // start[0] +1 && invisible endtype +1
}

static char **token_fill(t_table *tab, const char *s, char *set, int i[3]) 
{
    int     n;      //token id
    int     len;
    int     q[2];       // uniq_quotes ignore

    n = 0;
    q[0] = 0;
    q[1] = 0;
    len = ft_strlen(s);
    i[2] = -1;
    while (s[i[0]] && i[0] < len)
    {                   //sans espace ...
        if(!ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')  //  if not spc 
        {
            i[2] = i[0]; // token start = i[2]
            while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
            {                 
                q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;     //single_ignore simpl_q
                q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;     //single_ignore dbl_q
                i[0]++; // printf("DEBUG: n_fill -- i[2] = [%d][%d][%c]\n", n, i[0], s[i[0]]);     // NOT
            }           // ... spaceless token ++
            i[1] = i[0]; 
        }              // str avec espace
        if(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')  // ++ until spc found
        {
            i[1] = i[0]++; 
            while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
                i[0]++;
        }
        if (i[0] <= len && i[2] > -1) // still left && pass thru "nospaceland"
        {
            tab->token[n] = ft_substr((char *)s, i[2], (i[1] - i[2]));
            tab->token = ft_mx_ext(tab->token, tab->token[n]);          
            printf("token[%d] => ::%s::\n", n, tab->token[n]);
            n++;
        }           
    }
    return (tab->token);
}

char **init_split(char *input, char *set, t_table *tab)
{
    int     n;
    int     i[3];       // *arr pos: start, sub-end, end
    int     count[2];   // str sub len [0:start/1:end]

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    count[0] = 0;
    count[1] = 0;
    if (!input)
        return (NULL);    
    input = type_check(input, "<|>");   // padding endtype count 
    
    printf("DEBUG: pass_to_init :: %s \n", input);   

    n = token_count(input, set, count);  // word_count >.<
    if (n == -1)
        return (NULL);    // printf("token = %d::\n", n);
    tab->token = malloc(sizeof(char *) * (n + 1));   // malloc +2 EOT char
    if (!tab->token)
        return (NULL);
    tab->token = token_fill(tab, input, set, i);    // tab->cmds <<  set(" "), *s, i[] 
    return (tab->token);   // return clean token space-split args
}

/*
from parse.c
/// endtype-padding + token_split * 
    init_split => split *str by space only (quote rule (ok if both))
    word_count + ft_fill_token ... ... seems legit!
    *** init_split: trunk at space to make node part
*/