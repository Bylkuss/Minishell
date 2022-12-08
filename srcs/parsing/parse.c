/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/08 00:21:54 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

// t_token	*token_nodes(t_table *tab)	/* call by parse_  <<(token_ized)	*/
// {

    
// }

/*       char **args = tab->cmds  :  token chunk    */
static t_table *split_all(char **node, t_table *tab)  
{
    char **box;
    char *set;
    int     i;
    int     id;     // tkn_id     
    int     focus_id;
    int quotes[2];
    // char    ***cmdx;  // char number name-> x[itoa(x)]
    // char *cmd_line;

    i = -1;
    id = 0;
    focus_id = 0;

    quotes[0] = 0;
    quotes[1] = 0;
    set = "<|>";
    box = NULL;


    // tab->token->cmd = NULL;
    printf("split_:: ? node = _%d_\n",ft_mx_len(tab->node));
    while (node && node[++i])       
    {
        //args = tab->cmds[id]
            //        :: node_id[0]/node_id[len-1] {(attr = null) if (len = 2)}
            //        :: token->[cmd][attr][end] ==>> token->[cmd=id[0]] [attr] [end=id[len-1]] */
        node[i] = expand_vars(node[i], -1, quotes, tab);  
        //expand_var ...   
          printf("DEBUG: spl_ll vars_node_id[%d]::[%s]::\n", i, node[i]);
        node[i] = expand_path(node[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
        //expand_path ...
            printf("DEBUG: spl_ll path_node_id[%d]::[%s]::\n", i, node[i]);
        box = div_token(node[i], set, tab, id); 
        //div_token ...

                // if (!cmd_line)
                //     cmd_line = ft_substr(node[i], 0, ft_strlen(node[0]));
                // else
                //     cmd_line = ft_strjoin(cmd_line, node[i]);
                // if (ft_strchar_i("|", *box)) 
                //     id++;
        printf("DEBUG: split: div_token_id[%d]::[%s]::\n", id, *box);

    //token_node  need 
        if (ft_strchar_i(*box, set))        
        {
            printf("DEBUG: split_ll :: tkn_str_len[%d]::\n", ft_mx_len(tab->token->cmd));
                // printf("tk_id[%d] ==> ...%s... \n", id, tab->token->cmd[i]);
            tab->token->cmd = ft_mx_ext(tab->token->cmd, node[i]);
            tab->token->cmd = ft_mx_ext(tab->token->cmd, "\0");
            ++id;
        }
        else 
        {
            tab->token->cmd = ft_mx_ext(tab->token->cmd, node[i]);
        }
        if (id > focus_id && id <= tab->tk_num)
        {
            printf("DEBUG: .. .. FOCUS_id[%d]\n",focus_id);
            // tab->token = token_nodes(tab);
            // tab->cmds[id] = ft_mx_rpl(tab->cmds, tab->token->cmd, ft_mx_len(tab->token->cmd));
            mx_display_tab(tab->token->cmd);
            ft_mx_free(&tab->token->cmd);
            focus_id = id;            
        }
    // tab->token = token_nodes(tab);
    }
    
    //   ls -lta |wc -l >> out.txt   

    // mx_display_tab(cmdx[id]);
        // tab->token->tk_len += ft_mx_len(tab->node);
                // mx_rpl (arg , node)
                // ft_mx_rpl(&args, nodes, i);
                // //
                // // printf("mx_len == %d\n", i);
                // // free node
                // ft_mx_free(&nodes);

    // printf("DEBUG: split_all :: tk_id = %d\n", id);
    // printf("DEBUG: split all :: t->cmd = %s\n", tab->token->cmd[i]);
    return (tab); 
}

static t_token  *parse_args(t_table *tab)
{
    int i; // int is_exit; // is_exit = 0;
    // int tab_len;
    int tk_id;

    t_token *token;
    token = tab->token;

    i = 0;
    tk_id = 0;
    // tab_len = 0;
        //     tab >> tab->node  ::  substr( tab->cmds >> endtype ) 
        // if (tab->node)
    // printf("DEBUG: parse... tab->cmds >> \n");
        //create cmds ... token ... malloc both!
    
    tab = split_all(tab->node, tab); 
    // tab_len =  ft_mx_len(tab->node);
    // printf("DEBUG: parse >>node_num = [%d] \n",tab_len);

    // tab->cmds[tk_id] = ft_mx_rpl(tab->cmds, tab->node, tab_len);
    // tab_len = ft_mx_len(tab->cmds[i]);
    // printf("DEBUG: parse >>token_len = [%d] \n",tab->tk_num );

    //          pass nodes splited to be check /meta
    // token = token_nodes(tab);
    // printf("DEBUG: parse... tab->token >>\n");
    if (tab->cmds[tk_id])
    {
        // mx_display_str(*tx[0]);
        i = ft_mx_len(tab->cmds[tk_id]);
         printf("DEBUG: parse >>tab->cmds[0] len = %d >>\n", i);
    }

    token = token_nodes(tab);  
    mx_display_tab(token->cmd);
    //          node breaker =>   node_token == token_builder ...
        
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
    
    return (tab->token);
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
        mx_display_tab(tab->node);
        printf("DEBUG: check :: node_num ::%d::\n", n);
    }
    tab->token = parse_args(tab);    // tab->node        
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
