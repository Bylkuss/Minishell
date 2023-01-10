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

static char *node_padd(char *input, char *meta)
{
    char *srcs; //  start part str
    char *tmp;  //  sub str
    char *dest; //  end part str
    int p[4];   //ptr pos start/pos/end

    p[2] = 0;
    p[3] = 0;
    p[1] = ft_strchar_i(input, meta); // ret (index found charset into str
    if (p[1] == -1)
        return (input);
    else
    {
        p[0] = p[1] - 1;
        p[2] = p[1] + 1;
        p[3] = ft_strlen(input);
        // printf("the padd p[3] len [%d] \n", p[3]);
        if ((input[p[1] + 1]) == (input[p[1]]))   // twin chk ! 
            p[2] = p[1] + 2;
        printf("DEBUG : type_check :[%d]: %s \n\n", p[3], input);
        srcs = ft_substr((const char *)input, 0, (p[3] - (p[3] - p[1]))); 
        printf("DEBUG :: srcs_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);
        tmp  = ft_substr((const char *)input, p[1] , p[2] - p[1]); 
        printf("DEBUG :: tmp_check [%ld] ::%s: \n",ft_strlen(tmp), tmp);
        dest = ft_substr((const char *)input, p[2] , p[3] - p[2]); 
        printf("DEBUG :: dest_check [%ld] ::%s: \n",ft_strlen(dest), dest);
        if (input[p[0]] != 32)// tmp -1
            tmp = ft_strjoin(" ", tmp); //add spece before
        if (input[p[2]] != 32) //tmp + 1
            tmp = ft_strjoin(tmp, " ");  //add space after
        srcs = ft_strjoin(srcs, tmp);
        input = ft_strjoin(srcs, dest);
    } 
    return(input);
}

char *type_check(char *input, char *meta)
{
    char *srcs; //  start part str
    char *res;  //  sub str
    char *tmp;
    char *dest; //  end part str
    int p[4];   //ptr pos start/pos/end
    int padd;   // detected

    res = "\0";
    padd = 0;          
    p[2] = 0; //index ptr count 
    p[1] = 0;
    p[3] = ft_strlen(input);        // printf("type_check:: str_end_p[3] = %d\n", p[3]);
    while (padd == 0)
    {
        p[1] = ft_strchar_i(input, meta); // ret (index found charset into str
        if (p[1] == -1)
            padd = 1;
        p[0] = p[1] - 1;
        p[2] = p[1] + 1;
        if ((input[p[1] + 1]) == (input[p[1]]))   // twin chk ! 
            p[2] = p[1] + 2;
        srcs = ft_substr((const char *)input, 0, (p[3] - (p[3] - p[0]))); //bfore endtype                // printf("DEBUG :: srcs_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);
        tmp = ft_substr((const char *)input, p[0] , p[2] - p[0]); //etype pad                // printf("DEBUG :: tmp_check [%ld] ::%s: \n",ft_strlen(tmp), tmp);
        dest = ft_substr((const char *)input, p[2] , p[3] - p[2]); // left                // printf("DEBUG :: dest_check [%ld] ::%s: \n",ft_strlen(dest), dest);
        res = ft_strjoin(res, srcs);
        if (p[1] && (input[p[0]] != 32) || (input[p[2]] != 32))
            tmp = node_padd(tmp, meta);
        res = ft_strjoin(res, tmp); 
        input = dest;
    }
    input = ft_strjoin(res,dest);    // printf("DEBUG oo output_check [%ld] ::%s: \n",ft_strlen(input), input);
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
    return (i[1] + 2); // start[0] +1 && invisible endtype +1
}

static char **node_fill(t_table *tab, const char *s, char *set, int i[3]) 
{
    int     n;      //node id
    int     len;
    int     q[2];       // uniq_quotes ignore

    n = 0;
    q[0] = 0;
    q[1] = 0;
    len = ft_strlen(s);
    i[2] = -1;
    while (s[i[0]] && i[0] < len)
    {
        //sans espace ...
        if(!ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')  //  if not spc 
        {
            i[2] = i[0]; // node start = i[2]
            while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
            {                 
                q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;     //single_ignore simpl_q
                q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;     //single_ignore dbl_q
                i[0]++; // printf("DEBUG: n_fill -- i[2] = [%d][%d][%c]\n", n, i[0], s[i[0]]);     // NOT
            }   // ... spaceless node ++
            i[1] = i[0]; 
        }
        // str avec espace
        if(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')  // ++ until spc found
        {
            i[1] = i[0]++; 
            while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
                i[0]++;
        }
        if (i[0] <= len && i[2] > -1) // still left && pass thru "nospaceland"
        {
            tab->node[n] = ft_substr((char *)s, i[2], (i[1] - i[2]));
            tab->node = ft_mx_ext(tab->node, tab->node[n]);          
            printf("node[%d] => ::%s::\n", n, tab->node[n]);
            n++;
            if(i[0] == len)
            {
                tab->node[n] = ft_strdup("@\0");
                printf("node[%d] => ::%s::\n", n, tab->node[n]);
            }
        }           
    }
    return (tab->node);
}

//    ls -lat |head -2|wc -l> out.txt   
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
    input = type_check(input, "<|>");   // purify endtype
            // printf("DEBUG: pass_to_init :: %s \n", input);
    n = node_count(input, set, count);    // substr 
            printf("DEBUG: init_split  ::  node_count = %d \n", n ); 
    if (n == -1)
        return (NULL);
    tab->node = malloc(sizeof(char *) * (n + 1));   // malloc +2 EOT char
    if (!tab->node)
        return (NULL);
    tab->node = node_fill(tab, input, set, i);    // tab->cmds <<  set(" "), *s, i[] 
    // printf  ("DEBUG: end_init ::: node:[%d] \n", ft_mx_len(tab->node));
    return (tab->node);   // ret(tab->node)
}

/*
from parse.c
    init_split => split *str by space only (quote rule (ok if both))
    word_count + ft_fill_node ... ... seems legit!
    *** init_split: trunk at space to make token part
*/