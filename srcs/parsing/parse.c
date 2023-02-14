/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/13 23:26:25 by gehebert         ###   ########.fr       */
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
    cmd = tab->token; 
    n = ft_mx_len(cmd);
    printf("DEBUG:: redir_type tab->token{%s}, (len:%d)\n", cmd[n - 1] , n);
    tab->nods = 0;
//    ref[tab->nods] = 0; 
    // printf("DEBUG:: redir_type tab->token[id:%d] ref[%d] \n", tab->nods, ref[tab->nods]);

    while (++id < (n -1))
    {
        // tab->nods = tab->nod_num;   
        printf("DEBUG:: redir_type cmd[id:%d] str{%s} \n", id, cmd[id]);
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
                tab->nods++;  
                tab->refs[tab->nods] = id;                
            }
            // printf  ("DEBUG: id[%d] ::REDIR::{%d}:: nod_num[%d]\n", id, tab->node->etype, tab->nods);
            if (tab->node->etype != -1)
                printf  ("DEBUG: REDIR_ NEW_REF::ID[%d]== ETYPE(pos[%d])\n", tab->nods, tab->refs[tab->nods]);
            
        }
        // else
            tab->node->etype = -1;
    }
    tab->refs[tab->nods] = id;
    if (tab->node->etype == -1)
        tab->node->etype = 0;
//    tab->refs = ref;
    return (tab);
}

static t_table *split_all(t_table *tab)  
{
    int     i;
    int     quotes[2];

    i = -1;
    quotes[0] = 0;
    quotes[1] = 0;
    tab->nods = 1;
    
    printf("DEBUG/: split_all tab->token[id:%d] token{%s} \n", tab->nods, *tab->token);	
        // tab = redir_type(tab); // node_count:: *refs[id] = token_pos[array]
        // tab = node_alloc(tab); // node  alloc && node[array]    <<< init.c
        //
        //
    tab = redir_type(tab); // node_count:: *refs[id] = token_pos[array]
    tab = node_alloc(tab); // node  alloc && node[array]    <<< init.c
    while (tab->token[++i] && i <= tab->node->nod_len)       
    {
        //expand_var ...   meta-char- safe-check execeptions 
        tab->token[i] = expand_vars(tab->token[i], -1, quotes, tab);  
        //expand_path ...  cmd_chks legit!      
        tab->token[i] = expand_path(tab->token[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
       
            // printf("DEBUG: split_all tab->node->path == {%s} \n", tab->node->path);
    }
    printf("DEBUG:: split node->id[%d] OF nods[%d] << node...\n", tab->node->id, tab->nods);
    
            // printf("DEBUG:  nods    __%d__ ...\n", tab->nods);        
            // printf("DEBUG:  t->refs   __%d__ ...\n", tab->refs[tab->nods]); 
    return (tab); 
}


static t_table  *parse_args(t_table *tab)
{

    int is_exit;
    t_node *node;

    is_exit = 0;
    node = tab->node;
    tab->nods = 1;

    // tab = split_all(tab);      
    printf("DEBUG: into... parse\n");
  
    tab = div_node(split_all(tab), "<|>"); // node_builder:: redir//alloc

    printf("DEBUG:: parse: t->id[%d] OF [%d] << node...\n", node->id, tab->nods);
    tab->nods = 1;
    
    while (tab->nods)// <= tab->nod_num)
    {
        node = get_node(tab, tab->node, tab->nods);
        tab->node = node;
        g_status = builtins_handler(tab, tab->node);
        waitpid(-1, &g_status, 0);
        
        if (!is_exit && g_status == 13)
            g_status = 0;
        if (g_status > 255)
            g_status = g_status / 255;
        tab->nods--;     
    }
          
    if (tab->cmds && is_exit)
    {
        tab->nods = 0;
        ft_mx_free(tab->cmds);
        ft_mx_free(&tab->token);
        free_cont(tab->node);
        ft_mx_free(&tab->node->cmd);
        return (NULL);
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
