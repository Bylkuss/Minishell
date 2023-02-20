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

static t_table	*redir_type(t_table *tab) 
{
    char    **cmd;
    int     n;
    int     id;

    id = -1;
    cmd = ft_mx_dup(tab->token); 
    n = ft_mx_len(cmd);
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
                printf  ("DEBUG: REDIR_nods[%d] tkID[%d]== ETYPE(pos[%d])\n", tab->node->id, id, tab->refs[tab->node->id]);
                tab->node->id++;  
            }
            if (tab->node->etype > 1)
                tab->refs[tab->node->id] = id;
        }
    }
    if (  tab->refs[tab->node->id] < 1 && tab->node->etype == -1)
    {
        tab->refs[tab->node->id] = id;
        tab->node->etype = 0;
    }
    printf  ("DEBUG: REDIR_ Etype[%d]== ETYPE(pos[%d])\n", tab->node->etype, tab->refs[tab->node->id]);
    return (tab);
}

static t_table *split_all(t_table *tab)  
{
    int     i;
    int     quotes[2];

    i = -1;
    quotes[0] = 0;
    quotes[1] = 0;
    // printf("DEBUG:: split_all\n");// tab->token[id:%d] token{%s} \n", tab->nods, *tab->token);	
    tab = redir_type(tab); // node_count:: *refs[id] = token_pos[array]
    tab = node_alloc(tab); // node  alloc && node[array]    <<< init.c
    while (tab->token[++i] && i <= tab->node->nod_len)       
    {
        //expand_var ...   meta-char- safe-check execeptions 
        tab->token[i] = expand_vars(tab->token[i], -1, quotes, tab);  
        //expand_path ...  cmd_chks legit!      
        tab->token[i] = expand_path(tab->token[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));  
    }
    // maybe div_ here instead ... part by  part ... and free asap
    return (tab); 
}
        // printf("DEBUG:: split_ node->id[%d] t->nods[%d] \t.....\n", tab->node->id, tab->nods);
            // printf("DEBUG:  nods    __%d__ ...\n", tab->nods);        
            // printf("DEBUG:  t->refs max   __%d__ ...\n", tab->refs[0]); 


static t_table  *parse_args(t_table *tab)
{
    int is_exit;
    int id;

    is_exit = 0;
    tab->node = malloc(sizeof(t_node));
    printf("DEBUG:: ...BEGIN ... PARSE ...\n");
    tab = div_node(split_all(tab), "<|>"); // node_builder:: redir//alloc
        // printf("DEBUG:: parse: t->id[%d] OF [%d] << node...\n", node->id, tab->nods);
        // tab->node->id = 1;
    id = ft_lstsize(tab->cmdl);
    printf("DEBUG:: ready to go cmdl = %d ::\n", id);
    g_status = builtins(tab, tab->cmdl, &is_exit);
    while (id-- > 0)
        waitpid(-1, &g_status, 0);
    if (!is_exit && g_status == 13)
        g_status = 0;
    if (g_status > 255)
        g_status = g_status / 255;
    if (tab && is_exit)
    {
        printf("yo_ empty_ me_ g_status = %d__\n", g_status);
        ft_lstclear(&tab->cmdl,free_cont);
        ft_mx_free(tab->cmds);
        ft_mx_free(&tab->token);
        return (NULL);
    }
    return (tab);
}

void  *check_args(char *input, t_table *tab)    // main deploy >parse
{
    t_node *n;     
     
    if (!input)
        return (NULL);
    if (input[0] != '\0')
        add_history(input);
    tab->token = init_split(input, " ", tab);   // input* >>> tab->token**
    free(input);
    if (!tab->token)
    {
        chk_error(QUOTE, NULL, 1);
        return ("");
    }
    tab = parse_args(tab);                      // tab->token** >>> (tab->)node->cmd**  !!mearly not needed!!

    if (tab && tab->cmdl)
        n = tab->cmdl->content;
    if (tab && tab->cmdl && n  && n->cmd && ft_lstsize(tab->cmdl) == 1)
        tab->envp = ms_setenv("_", n->cmd[ft_mx_len(n->cmd) -1], tab->envp, 1);
    if (tab && tab->cmdl)
        ft_lstclear(&tab->cmdl, free_cont);    
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
