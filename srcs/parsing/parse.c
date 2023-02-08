/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/06 18:11:22 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;
/*
* etype spot endtype index (nod_len, nod_num)
*/
static t_table	*redir_type(t_table *tab) 
{
    char    **cmd;
    int     n;
    int     id;
    int     *ref;

    id = -1;
    //cmd = ft_mx_dup(tab->token); 
    cmd = tab->token; 
    n = ft_mx_len(cmd);   
    tab->node->id = 1;
    ref[tab->node->id] = 0; 
    while (id++ < (n -1))
    {
        tab->node->id = tab->nod_num;   
        if (cmd[id] && (id + 1) < (n - 1))
        {
            if (*cmd[id] == '<' &&  *cmd[id + 1] == '<')
                tab->node->endtype = 5;
            else if (*cmd[id] == '<')
                tab->node->endtype = 4;
            else if ( *cmd[id] == '>' && *cmd[id + 1] == '>')
                tab->node->endtype = 3;
            else if (*cmd[id] == '>')
                tab->node->endtype = 2;
            else if (*cmd[id] == '|')
            {
                tab->nod_num++;  
                tab->node->endtype = 1;
            }
            ref[tab->node->id] = id;                
            // printf  ("DEBUG: id[%d] ::REDIR::{%d}:: nod_num[%d]\n", id, tab->node->endtype, tab->nod_num);
            if (tab->node->endtype != -1)
                printf  ("DEBUG: REDIR_ NEW_REF::ID[%d]== ETYPE(pos[%d])\n", tab->node->id, ref[tab->node->id]);
        }
        // else
            tab->node->endtype = -1;
    }
    ref[tab->node->id] = id;
    if (tab->node->endtype == -1)
        tab->node->endtype = 0;
    tab->refs = ref;
    return (tab);
}

static t_table *split_all(t_table *tab)  
{
    int     i;
    int     tkn_id;     
    int quotes[2];

    i = -1;
    tab->node->id = 1;
    tkn_id = 1;
    quotes[0] = 0;
    quotes[1] = 0;

    // need to build get_node HERE...
        // set node->cmd** ==> token[cmd] + token[arg]
        // set node->path* =>> (!is_buitins) 
        // (if) set node->full*  ===>> {"cmd"+" "+"arg"...} (in case)
        // set endtype  ==>  node->endtype  ==> behavior related!
        // infile=0; outfile=1; 
    // tab = node_alloc(tab); // malloc each node + each node[cmd]    
    while (tab->token[++i] && tkn_id <= tab->nod_num)       
    {
        //expand_var ...   meta-char- safe-check execeptions 
        tab->token[i] = expand_vars(tab->token[i], -1, quotes, tab);  
        //expand_path ...        
        tab->token[i] = expand_path(tab->token[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
       
        	// printf("DEBUG/: split_all tab->token[id:%d] token{%s} \n", i, tab->token[i]);	
            // printf("DEBUG: split_all tab->node->path == {%s} \n", tab->node->path);
    }
    // tab->node = get_node(tab, tab->node, tkn_id);
    // tab = div_node(tab, "<|>"); // padd endtype + set node 
    return (tab); 
}


static t_table  *parse_args(t_table *tab)
{

    int is_exit;
    t_node *node;

    is_exit = 0;
    node = tab->node;
    tab->node->id = 1;
    printf("DEBUG: into... parse\n");
    tab = redir_type(tab); // *refs[id] nod_num [end_pos] == nod_len

        // printf("DEBUG:  nod_num    __%d__ ...\n", tab->nod_num);        
        // printf("DEBUG:  t->tk->id __%d__ ...\n", tab->node->id); 
        // printf("DEBUG:  t->refs   __%d__ ...\n", tab->refs[tab->node->id]); 

    tab = node_alloc(tab); // malloc each node + each node[array]    

    tab = split_all(tab);      

    tab = div_node(tab, "<|>"); // padding  etype + set node

    tab->node->id = 1;
    // printf("DEBUG:: parse: t->id[%d] OF [%d] << node...\n", tab->node->id, tab->nod_num);
    
    while (tab->node->id <= tab->nod_num)
    {
        node = get_node(tab, tab->node, tab->node->id);
        tab->node = node;
        g_status = builtins_handler(tab, tab->node);
        waitpid(-1, &g_status, 0);
        
        if (!is_exit && g_status == 13)
            g_status = 0;
        if (g_status > 255)
            g_status = g_status / 255;
        tab->node->id++;     
    }
          
    if (tab->cmds && is_exit)
    {
        tab->nod_num = 0;
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

    //node should be execute here...
    ///
        // builtins_handler(tab->token[0], tab->envp);
        // builtins_handler(input, tab->envp);
    
        // if (tab->cmds[0])
        // if (tab->cmds && tab->nod_num > 0)
        //    if (tab && tab->cmds && tab->node && tab->nod_num > 0)
        //  {
                // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
                //  - 1], p->envp, 1);                                    
                //     ft_lstclear(&p->cmds, free_content);
        // exit(0);
        // }
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
