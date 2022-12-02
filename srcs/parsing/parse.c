/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/29 18:58:29 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

/*       char **args = tab->cmds  :  token chunk    */
static char ***split_all(char **args, t_table *tab)  
{
    char    ***cmdx;  // char number name-> x[itoa(x)]
    // char    *x;         // char * token selector
    // int     x;              // cmdx -> num factor
    int i;
    int quotes[2];

    i = -1;
    // x = 0;
    cmdx = NULL;
    
    printf("DEBUG : into... split all\n");
    while (args && args[++i])       
    {
        // args = tab->cmds[id]
            //        :: node_id[0]/node_id[len-1] {(attr = null) if (len = 2)}
            //        :: token->[cmd][attr][end] ==>> token->[cmd=id[0]] [attr] [end=id[len-1]] */
        args[i] = expand_vars(args[i], -1, quotes, tab);  
        //expand_var ...  
        args[i] = expand_path(args[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));              
        //expand_path ...
        tab->node = div_token(args[i], "<|>", tab); 
        //div_token ...
        cmdx[i] = ft_mx_ext(cmdx[i], args[i]);
        tab->token->tk_len += ft_mx_len(tab->node);




                // mx_rpl (arg , node)
                // ft_mx_rpl(&args, nodes, i);
                // //
                // // printf("mx_len == %d\n", i);
                // // free node
                // ft_mx_free(&nodes);

                // mx_display_tab(nodes);
    }
    // mx_display_tab(args);
    return (cmdx); 
}


//  parse still w/ nodes

t_table  *parse_args(t_table *tab)
{
    int i;// int is_exit; // is_exit = 0;
    // t_token *token;
    // token = tab->token;

    i = 0;
    //              tab >> tab->node  ::  substr( tab->cmds >> endtype ) 
    tab->cmds = split_all(tab->node, tab); // pass nodes splited to be check /meta
    printf("DEBUG: parse... tab->cmds\n");

    //              node breaker =>   node_token == token_builder ...
    tab->token = token_nodes(tab);  
    printf("DEBUG: parse... tab->token\n");
    
    //              

    // while(tab->node[i] != NULL)
    // {
    //     mx_display_str(tab->node[i]);
    //     i++;

    // }


        /*  tab->node [*str]  sep.space. node -ID.less
            tab >> tab->token-> ... arg-set value ...TBD            
            //  
            if (tab->token)
                display_tkn(tab);
            if (!tab->node)
                return (tab->token);

            // tab->
            // i = ft_lstsize(tab->cmds);
            // g_status = builtin(p, p->cmds, &is_exit, 0);             
         */    
    i = 0;
    while (i-- > 0)
        waitpid(-1, &g_status, 0);
    if (g_status > 255)
        g_status = g_status / 255;
    /*
        // if (!is_exit && &g_status == 13)
        //     g_status = 0;
        // if (args && is_exit)
            // {
            //     ft_lstclear(&p->cmds, free_content);
            //     return (NULL);
        // }
    */
    return (tab);
}

t_table  *check_args(char *input, t_table *tab)  // main deply >parse
{
    // int i;

    // i = 0;
    if (!input)
    {
        printf("exit\n");
        return (NULL);
    }
    if (input[0] != '\0')
        add_history(input);
        
        
    tab->node = init_split(input, " "); // space split 

    if (tab->node)
    {

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
