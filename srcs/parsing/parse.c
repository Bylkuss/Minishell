/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/03 00:24:13 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

/*       char **args = tab->cmds  :  token chunk    */
static char ***split_all(char **node, t_table *tab)  
{
    char    ***cmdx;  // char number name-> x[itoa(x)]
    int i;
    int quotes[2];

    i = -1;
    // x = 0;
    cmdx = NULL;
    
    ft_mx_rpl(cmdx, tab->node, ft_mx_len(tab->node));
    
    while (node && node[++i])       
    {
        // args = tab->cmds[id]
            //        :: node_id[0]/node_id[len-1] {(attr = null) if (len = 2)}
            //        :: token->[cmd][attr][end] ==>> token->[cmd=id[0]] [attr] [end=id[len-1]] */
        node[i] = expand_vars(node[i], -1, quotes, tab);  
        //expand_var ...  
        node[i] = expand_path(node[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
        //expand_path ...
        tab->cmds[i] = div_token(node[i], "<|>", tab); 
        //div_token ...
        cmdx[i] = ft_mx_ext(tab->cmds[i], node[i]);
    }
        // tab->token->tk_len += ft_mx_len(tab->node);
                // mx_rpl (arg , node)
                // ft_mx_rpl(&args, nodes, i);
                // //
                // // printf("mx_len == %d\n", i);
                // // free node
                // ft_mx_free(&nodes);

                // mx_display_tab(nodes);
    printf("DEBUG : into... split all :: id = %d\n", i);
    return (cmdx); 
}



//  parse still w/ nodes
t_table  *parse_args(t_table *tab)
{
    int i; // int is_exit; // is_exit = 0;
        // t_token *token;
        // token = tab->token;
        // i = 0;
        //     tab >> tab->node  ::  substr( tab->cmds >> endtype ) 
            // if (tab->node)
    printf("DEBUG: parse... tab->node >> tab->cmds\n");
    tab->cmds = split_all(tab->node, tab); 
    //          pass nodes splited to be check /meta
    tab->token = token_nodes(tab);  
    //          node breaker =>   node_token == token_builder ...
    printf("DEBUG: parse... tab->token\n");
        /*  tab->node [*str]  sep.space. node -ID.less
            tab >> tab->token-> ... arg-set value ...TBD            
            // tab->
            // i = ft_lstsize(tab->cmds);
            // g_status = builtin(p, p->cmds, &is_exit, 0);             
         */    
    i = 0;
    while (i-- > 0)
        waitpid(-1, &g_status, 0);
    if (g_status > 255)
        g_status = g_status / 255;
    
       // if (!is_exit && &g_status == 13)
        //     g_status = 0;
        // if (args && is_exit)
        // {
        //     ft_lstclear(&p->cmds, free_content);
        //     return (NULL);
        // }
    
    return (tab);
}

t_table  *check_args(char *input, t_table *tab)  // main deply >parse
{
     int n;     //int node
    //  int i;    // i = 0;
    n = 0;
    if (!input)
    {
        printf("exit\n");
        return (NULL);
    }
    if (input[0] != '\0')
        add_history(input);
        
    tab->node = init_split(input, " ", tab); // space split 
    if (tab->node)
    {   
        n = ft_mx_len(tab->node);
        printf("DEBUG: check :: node_len ::%d::\n", n);
        // mx_display_str(tab->node[n - 1]);
        // mx_display_str(tab->node[n - 3]);
    }

    tab = parse_args(tab);    // tab->node        
    // while(tab->node)
        // {
        //     i = 0;
        //     while(*tab->node[i] != '\0')
        //     {
        //         printf("\n check node > [%s] \n", tab->node[i]);
        //         i++;
        //     }
        //     tab->node++;
        // }
        // *tab->cmds = node_check(tab->node, "|");

        // }
            // printf("\nOK TEST INPUT :: :: END\n");   
                // mx_display_tab(tab->cmds);
                // display_tkn(tab);
                // len = ft_mx_len(tab->node);
                // printf("\n%d :::\n", len);
                // return (tab);
        // if (tab->cmds[0])
        //     printf("DEBUG : into... check_arg\n");
        // exit(0);
            // if (tab->cmds && tab->tk_num > 0)
            // else
            //     return (NULL);
        /*
                    if (tab && tab->token)
                        display_tkn(tab);

        token need to be ID _cmd, _attr, _end         */
                /*
                    if (tab && tab->cmds && tab->token && tab->tk_num > 0)
                    {
                        // mx_display_tab(tab->cmds);
                        // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
                        //  - 1], p->envp, 1);                                    
                            //     ft_lstclear(&p->cmds, free_content);
        */
    // }

    // free(input);
    return (tab); 
}

/*
from check.c
    check_args  => take input to be init_split to build table command
    space_split    => will do that init_split into a tab **       ==> init_split.c
    parse_args  => call fill_node  return *p (list-> p.cmds)    ==> nodes.c
    split_all   =>  token's alternate end if it's not! 
                    div_token  ('<','>','|')                    ==> divide.c
                    expand_vars & expand_path                   ==> expand.c
    *** so in my mind a token is : CMD + ARG + END 
    *** in fact ARG is facultative
*/
