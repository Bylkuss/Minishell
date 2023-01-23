/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/22 18:31:30 by gehebert         ###   ########.fr       */
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
    printf  ("DEBUG: tk_num[%d]\n", tab->tk_num);
    // printf  ("DEBUG: etype::  total node:[%d] \n", n);
   
    tab->token->id = 0;
    ref[tab->token->id] = 0; 
    while (id++ <= n)
    {
        tab->token->id = tab->tk_num; 
        ref[tab->token->id] = id;
        if (cmd[id] && (id < n))
        {
            if (*cmd[id] == '<' && cmd  && *cmd[id + 1] == '<')
                tab->token->id = tab->tk_num++; 
            else if (*cmd[id] == '<')
                 tab->token->id = tab->tk_num++; 
            else if (*cmd[id] == '>' && cmd  && *cmd[id + 1] == '>')
                 tab->token->id = tab->tk_num++; 
            else if (*cmd[id] == '>')
                  tab->token->id = tab->tk_num++; 
            else if (*cmd[id] == '|')
                  tab->token->id = tab->tk_num++;   
            else if (*cmd[id] == '@')
                  tab->token->id = tab->tk_num++; 
            ref[tab->token->id] = id; 
            if (tab->token->endtype != -1)
            {
                printf  ("DEBUG: tk_num[%d]\n", tab->tk_num);
                //    printf  ("DEBUG: tk_num[%d]: etype_pos[%d]  \n", tab->tk_num, ref[tab->token->id]);
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

    // token_node ...
    tab = token_nodes(tab); // malloc each token + each token[cmd]    
    tab = div_token(tab, "<|>"); // padd endtype + set token 
    while (tab->node[++i] )//&& tkn_id <= tab->tk_num)       
    {
        //expand_var ...   
        tab->node[i] = expand_vars(tab->node[i], -1, quotes, tab);  
        	// printf("DEBUG/: split_all tab->node[id:%d] node{%s} \n", i, tab->node[i]);	
        //expand_path ...         
        tab->node[i] = expand_path(tab->node[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
            // printf("DEBUG: split_all tab->token->path == {%s} \n", tab->token->path);
    }
    return (tab); 
}

static t_table  *parse_args(t_table *tab)
{
    // int i;    // i = 0;
    // int type_id;    // tk_id = 0;
    int is_exit;
    int tk_id;
    // char *set;
    t_token *token;

    token = tab->token;
    is_exit = 0;
    // set = "<|>";
    tab->token->id = 0;
    printf("DEBUG: into... parse\n");
    tab = token_etype(tab); // *refs[id] tk_num [end_pos] == tk_len
        printf("DEBUG: #token[%d] ... ...\n", tab->tk_num);     
            // token_node ...
            // tab = token_nodes(tab); // malloc each token + each token[cmd]
        
    // split_all
    tab = split_all(tab); 
        // tab = div_token(tab, set); 
        
        /*  tab->node [*str]  sep.space. node -ID.less
            tab >> tab->token-> ... arg-set value ...TBD            
            i = ft_lstsize(tab->cmds);     */
           // g_status = builtin(p, p->cmds, &is_exit, 0);       
   
    token = get_token(tab, token, tk_id);
    while (tab->token->endtype >= 0)
    {
        // first get token 
            // all of them 
            // then do it
            // free content...


        // display_one_tkn(token, token->id);
        g_status = is_builtin(token);       
        printf("\nDEBUG : is_builtin {%d}::\n", g_status);     
            builtins_handler(tab, token, token->id);
        // if (tab->token->endtype == 0)
        //     tab->token->tk_len--;
        // if (g_status == 1)
        // else
        //     execmd(tab, tab->token, tk_id);
        // printf("DEBUG : g_status << {%d} >>::\n", g_status);     

        // free_cont(token, tk_id);
        tk_id--;
        tab->token->id++;
        // tab->tk_num--;
        // printf("DEBUG: #token[%d] . . .\n", tab->tk_num);     
        if (tk_id <= 0 )//|| tab->tk_num == 0)
            break;

   }
    // builtins_handler(input, tab->envp);
   
    tk_id = tab->tk_num;
    while (tk_id-- > 0)
        waitpid(-1, &g_status, 0);
    if (g_status > 255)
        g_status = g_status / 255;
        //
    if (!is_exit && g_status == 13)
        g_status = 0;

    if (tab->cmds && is_exit)
    {

        ft_mx_free(tab->cmds);
        return (NULL);
    }
    
    return (tab);
}

void  *check_args(char *input, t_table *tab)    // main deply >parse
{
    int n;     //int node
     
    n = 0;
    if (!input)
        return (NULL);
    if (input[0] != '\0')
        add_history(input);
    // tab->node        
    tab->node = init_split(input, " ", tab);    // space split  checked!!!
    // parse
    tab = parse_args(tab);

    //token should be execute here...
    ///
        // builtins_handler(tab->node[0], tab->envp);
        // builtins_handler(input, tab->envp);
    
        // if (tab->cmds[0])
        // if (tab->cmds && tab->tk_num > 0)
        //    if (tab && tab->cmds && tab->token && tab->tk_num > 0)
        //  {
                // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
                //  - 1], p->envp, 1);                                    
                //     ft_lstclear(&p->cmds, free_content);
        // exit(0);
        // }
    free(input);
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
