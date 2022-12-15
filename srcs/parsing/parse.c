/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/13 10:24:49 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

static t_table	*token_etype(t_table *tab) 
{
    char    **cmd;
    int     n;
    int     id;
    int     *ref;

    id = -1;
    cmd = tab->node; 
    n = ft_mx_len(cmd);
   
    tab->token->id = 0;
    ref[tab->token->id] = 0; 
    while (id++ <= n)
    {
        tab->token->id = tab->tk_num; 
        ref[tab->token->id] = id;
        if (cmd[id] && (id < n))
        {
            if (*cmd[id] == '<' && cmd  && *cmd[id + 1] == '<')
            {
                tab->token->endtype = 5;
                tab->token->id = tab->tk_num++; 
                ref[tab->token->id] = id; 
            }
            else if (*cmd[id] == '<')
            {
                tab->token->endtype = 4;
                 tab->token->id = tab->tk_num++; 
                ref[tab->token->id] = id; 
            }
            else if (*cmd[id] == '>' && cmd  && *cmd[id + 1] == '>')
            {
                tab->token->endtype = 3;
                 tab->token->id = tab->tk_num++; 
                ref[tab->token->id] = id; 
            }
            else if (*cmd[id] == '>')
            {
                tab->token->endtype = 2;
                  tab->token->id = tab->tk_num++; 
                ref[tab->token->id] = id;  
            }
            else if (*cmd[id] == '|')
            {
                tab->token->endtype = 1;
                  tab->token->id = tab->tk_num++;   
                ref[tab->token->id] = id;     
            }
            else if (*cmd[id] == '@')
            {
                tab->token->endtype = 0;     
                  tab->token->id = tab->tk_num++; 
                ref[tab->token->id] = id; 
            }
            if (tab->token->endtype != -1)
            {
                printf  ("DEBUG: tk_num[%d]: etype_pos[%d]  \n", tab->tk_num, ref[tab->token->id]);
                tab->token->endtype = -1;   
            }
        }
    }
    tab->refs = ref;
    return (tab);
}

static t_table *split_all(t_table *tab)  
{
  
    
    int     i;
    int     tkn_id;     
    int quotes[2];

    i = -1;
    tab->token->id = 1;
    tkn_id = 0;
    quotes[0] = 0;
    quotes[1] = 0;

    while (tab->node[++i] && tkn_id <= tab->tk_num)       
    {
        //expand_var ...   
        tab->node[i] = expand_vars(tab->node[i], -1, quotes, tab);  
        //expand_path ...         
        tab->node[i] = expand_path(tab->node[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
    }
    return (tab); 
}

static t_table  *parse_args(t_table *tab)
{
    int i; // int is_exit; // is_exit = 0;
    int type_id;
    int tk_id;
    char *set;

    t_token *token;
    token = tab->token;
    i = 0;
    tk_id = 0;
    set = "<|>";
    tab->token->id = 0;
    tab = token_etype(tab);
        //  >endtype< token[id]  (tab->tk_num)
        //  >endtype< node[pos] (token->tk_len) 
        // printf("DEBUG: token endtype #[%d]\n\n", tab->tk_num);     
    // token_node ...
    tab = token_nodes(tab); //cpy token to cmds ...
    // split_all
    tab = split_all(tab); 
    //  div_token could be after that ... in fact. div. dont need to b loop...
    tab = div_token(tab, set); 
    // mx_display_str(tab->cmds[1][1]);
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
    //  int n;     //int node
     
    //  n = 0;
    if (!input)
        return (NULL);
    if (input[0] != '\0')
        add_history(input);
    tab->node = init_split(input, " ", tab); // space split 
        // n = ft_mx_len(tab->node);
        // printf("DEBUG: check :: node_num ::%d::\n", n);
        //     mx_display_tab(tab->node);  
        // }
    tab = parse_args(tab);    // tab->node        
        // if (tab->cmds[0])
        //     printf("DEBUG : into... check_arg\n");
        // if (tab->cmds && tab->tk_num > 0)
        // exit(0);
        //    if (tab && tab->cmds && tab->token && tab->tk_num > 0)
          //  {
                // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
                //  - 1], p->envp, 1);                                    
                //     ft_lstclear(&p->cmds, free_content);
            // }
      // free(input);
    return (tab); 

/*
from check.c
    check_args  => take input to be init_split to build table command
    init_split   => will do that init_split into a tab **       ==> init_split.c
    parse_args  => call fill_node  return *p (list-> p.cmds)    ==> nodes.c
    split_all   =>  token's alternate end if it's not! 
                    div_token  ('<','>','|')                    ==> divide.c
                    expand_vars & expand_path                   ==> expand.c
    *** so in my mind a token is : CMD + ARG + END 
    *** in fact ARG is facultative
*/
}
