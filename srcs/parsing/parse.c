/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/15 21:52:12 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;
/*
* etype spot etype index (nod_len, nod_num)
*/
static t_table	*redir_type(t_table *tab) 
{
    char    **cmd;
    int     n;
    int     id;
    // int     *ref;

    id = -1;
    cmd = ft_mx_dup(tab->token); 
    n = ft_mx_len(cmd);
    // printf("DEBUG:: redir_type last token :: tab->token{%s}, (len:%d)\n", cmd[n - 1] , n);
    tab->nods = 1;
    tab->node->id = 1;
    tab->refs[tab->node->id] = 0; 
    tab->refs[0] = n ;

    tab->node->etype = -1;
    while (++id < (n - 1))
    {
        tab->nods = tab->node->id;
        tab->node->etype = -1;
        if (cmd[id] && (id + 1) < (n - 1))
        {
            if (*cmd[id] == '<' &&  *cmd[id + 1] == '<')
                tab->node->etype = 5;
            else if (*cmd[id] == '<')
                tab->node->etype = 4;
            else if ( *cmd[id] == '>' && *cmd[id + 1] == '>')
                tab->node->etype = 3;
            else if (*cmd[id] == '>')
                tab->node->etype = 2;
            else if (*cmd[id] == '|')
            {
                tab->node->etype = 1;
                tab->refs[tab->node->id] = id;                
                // printf  ("DEBUG: REDIR_nods[%d] tkID[%d]== ETYPE(pos[%d])\n", tab->node->id, id, tab->refs[tab->node->id]);
                tab->node->id++;  
            }
            if (tab->node->etype > 1)
            {
                tab->refs[tab->node->id] = id;
                // printf  ("DEBUG: REDIR_ tkID[%d]== ETYPE(pos[%d])\n", id, tab->refs[tab->node->id]);
            }
        }
    }
    if (tab->node->etype == -1)
    {
        tab->refs[0] = id;
        tab->node->etype = 0;
    }
    return (tab);
}

static t_table *split_all(t_table *tab)  
{
    int     i;
    int     quotes[2];

    i = -1;
    quotes[0] = 0;
    quotes[1] = 0;
    tab->node->id = 1;
    
    // printf("DEBUG/: split_all tab->token[id:%d] token{%s} \n", tab->nods, *tab->token);	
        // tab = redir_type(tab); // node_count:: *refs[id] = token_pos[array]
        // tab = node_alloc(tab); // node  alloc && node[array]    <<< init.c
        //
        //
    tab = redir_type(tab); // node_count:: *refs[id] = token_pos[array]
    printf("DEBUG:: split_ node->id[%d] t->nods[%d] \t.....\n", tab->node->id, tab->nods);
        // printf("DEBUG:: split ref[id:%d] OF ref{value:%s} << node...\n", tab->node->id, tab->token[tab->refs[tab->node->id]]);
    tab = node_alloc(tab); // node  alloc && node[array]    <<< init.c
    while (tab->token[++i] && i <= tab->node->nod_len)       
    {
        //expand_var ...   meta-char- safe-check execeptions 
        tab->token[i] = expand_vars(tab->token[i], -1, quotes, tab);  
        //expand_path ...  cmd_chks legit!      
        tab->token[i] = expand_path(tab->token[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
       
    }
    
            // printf("DEBUG:  nods    __%d__ ...\n", tab->nods);        
            // printf("DEBUG:  t->refs max   __%d__ ...\n", tab->refs[0]); 
    return (tab); 
}


static t_table  *parse_args(t_table *tab)
{

    int is_exit;
    t_node *node;

    is_exit = 0;
    tab->node = init_node(tab);
    node = tab->node;
    printf("DEBUG:: ...BEGIN ... PARSE ...\n");
    tab = div_node(split_all(tab), "<|>"); // node_builder:: redir//alloc
        // printf("DEBUG:: parse: t->id[%d] OF [%d] << node...\n", node->id, tab->nods);
    node->id = 1;
    while (node->id <= tab->nods)// <= tab->nod_num)
    {
        // tab->node = get_node(tab, tab->node, tab->node->id);
        g_status = builtins_handler(tab, node);
        waitpid(-1, &g_status, 0);
        
        if (!is_exit && g_status == 13)
            g_status = 0;
        if (g_status > 255)
            g_status = g_status / 255;
        node->id++; 
    }
    tab->node = node;
    if (tab->nods == 0)// && is_exit)
    {
        printf("yo_ empty_ me_\n");
        ft_mx_free(&tab->node->cmd);
        free_cont(tab->node);
        ft_mx_free(tab->cmds);
        ft_mx_free(&tab->token);
    }
    return (tab);
}

void  *check_args(char *input, t_table *tab)    // main deploy >parse
{
    int n;     
     
    n = 0;
    if (!input)
        return (NULL);
    if (input[0] != '\0')
        add_history(input);
    tab->token = init_split(input, " ", tab);   // input* >>> tab->token**
    if (!tab->token)
        return ("");
    tab = parse_args(tab);                      // tab->token** >>> (tab->)node->cmd**  !!mearly not needed!!
    free(input);

    // update-- envp -- should be execute here...
    ///
        //if nod_num == 0 
    /// update env 
        // free -> tab (content)
        // empty-> arrays
        // close -- next
    
    return (tab); 

/*
from check.c
    check_args  => take input to be init_split to build table command
    init_split   => will do that init_split into a tab **       ==> init_split.c
    parse_args  => call fill_token  return *p (list-> p.cmds)    ==> tokens.c
    split_all   =>  node's alternate end if it's not! 
                    div_node  ('<','>','|')                    ==> divide.c
                    expand_vars & expand_path                   ==> expand.c
    *** so in my mind a node is : CMD + ARG + END 
    *** in fact ARG is facultative

    ls -lt -a| head -3|wc -w>>out.txt
    ls -lt>>popox.txt  

*/ 
}
