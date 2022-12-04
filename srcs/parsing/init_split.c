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
    char *srcs; //  start part str
    char *tmp;  //  sub str
    char *dest; //  end part str
    int p[4];   //ptr pos start/pos/end

    p[3] = 0; // ptr strlen..    
    p[1] = ft_strchr_i((char *)input, *meta);
    if (p[1])
    {
        p[0] = p[1] - 1;
        p[2] = p[1] + 1;
        p[3] = ft_strlen(input);
        if ((input[p[1] + 1]) == 124)
            p[2] = p[1] + 2;
        // printf("DEBUG : pipe_check :[%d]: %s \n\n", p[3], input);
        srcs = ft_substr((const char *)input, 0, (p[3] - (p[3] - p[1]))); // printf("DEBUG :: srcs_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);
        tmp  = ft_substr((const char *)input, p[1] , p[2] - p[1]); // printf("DEBUG :: tmp_check [%ld] ::%s: \n",ft_strlen(tmp), tmp);
        dest = ft_substr((const char *)input, p[2] , p[3] - p[2]); // printf("DEBUG :: dest_check [%ld] ::%s: \n",ft_strlen(dest), dest);
        if (input[p[0]] != 32)// tmp -1
            tmp = ft_strjoin(" ", tmp);
        if (input[p[2]] != 32) //tmp + 1
            tmp = ft_strjoin(tmp, " ");  
        srcs = ft_strjoin(srcs, tmp);
        input = ft_strjoin(srcs, dest);
    }    
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
            }
            else
                i[0]++;
        }
        return (i[1] + 1);
}

// ls -lat | wc -l > out.txt
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
    while (s[i[0]] && i[0] <= len)
    {
        i[2] = i[0];
        while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
        {
            printf("DEBUG: n_fill -- i[0] = [%d][%c]\n", i[0], s[i[0]]);     // NOT
            q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;     //single_ignore
            q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;     //single_ignore
            i[0]++;
        }
        if(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')                      // spc found
        {
            i[1] = i[0];
            printf("DEBUG: n_fill XX i[1] = [%d][%c]\n", i[1], s[i[1]]);   // spc found
            i[0]++;
            // printf("DEBUG: n_fill OO i[0] = [%d][%c]\n", i[0], s[i[0]]);    // D: trouv
        }
        if (i[0] <= len)
        {
            // if( i[0] == len)
            //     i[2] = i[0] - 1;
            tab->node[n] = ft_substr((char *)s, i[2], (i[1] - i[2])); 
            printf("DEBUG:  node[%d]_len = _%ld_\n", n, ft_strlen(tab->node[n]));
            tab->node = ft_mx_ext(tab->node, tab->node[n]);
            i[2] = i[0]; // 1
            // printf("DEBUG: n_fill >< i[2] = [%d][%c]\n", i[2], s[i[2]]);   // spc found
            n++;
        }
        // else
        //     break;
            
    }
            tab->node = ft_mx_ext(tab->node, "\0");
    mx_display_tab(tab->node);
    return (tab->node);
}
// ls -lat | wc -l > out.txt
/*    (old spc_split) readline input _init_split_  NODE MAKER   */
char **init_split(const char *s, char *set, t_table *tab)
{
    // char    **;  // to be chang >> tab->node
    char    *input;
    int     n;
    int     i[3];       // *arr pos: start, sub-end, end
    int     count[2];   // str sub len [0:start/1:end]
    // int *v;

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    count[0] = 0;
    count[1] = 0;
    
    if (s)
        input = pipe_check((char *)s, "|");
    else
        return (NULL);
    printf("DEBUG: pass_to_init :: %s \n", input);
    n = node_count((const char *)input, set, count);     // substr 
    if (n == -1)
        return (NULL);
    tab->node = malloc(sizeof(char *) * (n + 1)); //strc malloc
    if (!tab->node)
        return (NULL);
    tab->node = node_fill(tab, input, set, i);    // tab->cmds <<  set(" "), *s, i[] 
    printf("DEBUG: init_split  ::  node = %d \n", n);      // DEBUG
    // tab->node[n] = NULL; 
    return (tab->node);   // ret(tab->node)
}

    // mx_display_str(input);
        // t_token *token;
            // token = tab->token; 
            // if (!token)
            //     exit(0);
            //     printf("TOKEN_ID:\t%d\n", tab->tk_num); // how many tkn
            //     printf("\nCMD== %s ==  \t", tab->token->cmd[id]); // 
            //     if (tab->token->tk_len > 2 )
            //         printf("ARG == %s == \t", tab->token->cmd[++id]);   
        // printf("END_TYPE == %d == \n", tab->token->endtype);   
    // mx_display_tab(arr);
/*
from parse.c
    init_split => split *str by space only (quote rule (ok if both))
    word_count + ft_fill_node ... ... seems legit!
    *** init_split: trunk at space to make token part
*/