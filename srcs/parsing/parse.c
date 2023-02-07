/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/07 00:58:29 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;
/*
* etype spot endtype index (tk_len, tk_num)
*/
static t_table	*redir_type(t_table *tab) 
{
    char    **cmd;
    int     n;
    int     id;
    int     *ref;

    id = -1;
    cmd = tab->node; 
    n = ft_mx_len(cmd);   
    // printf  ("DEBUG: node_num[%d]\n", n);
    // printf  ("DEBUG: node_num[%d]::value{%s}\n", n,cmd[n-1]);
    
    tab->token->id = 0;
    ref[tab->token->id] = 0; 
    while (id++ <= (n ))
    {
        tab->token->id = tab->tk_num;      
        if (cmd[id] && (id + 1) < (n - 1))
        {
            if (*cmd[id] == '<' &&  *cmd[id + 1] == '<')
                tab->token->endtype = 5;
            else if (*cmd[id] == '<')
                tab->token->endtype = 4;
            else if ( *cmd[id] == '>' && *cmd[id + 1] == '>')
                tab->token->endtype = 3;
            else if (*cmd[id] == '>')
                tab->token->endtype = 2;
            else if (*cmd[id] == '|')
            {
                tab->tk_num++;  
                tab->token->endtype = 1;
            }
            ref[tab->token->id] = id;                 
        }
        // tab->token->endtype = -1;
    }
    // printf  ("DEBUG: REDIR_ ->endtype [%d]\n", tab->token->endtype);
    // printf  ("DEBUG: REDIR_ ->tk_num [%d]\n", tab->tk_num);
    if (tab->token->endtype == -1)
    {
        ref[tab->token->id] = id - 1;
        tab->token->endtype = 0;
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
    tkn_id = 1;
    quotes[0] = 0;
    quotes[1] = 0;

    // need to build get_token HERE...
        // set token->cmd** ==> node[cmd] + node[arg]
        // set token->path* =>> (!is_buitins) 
        // (if) set token->full*  ===>> {"cmd"+" "+"arg"...} (in case)
        // set endtype  ==>  token->endtype  ==> behavior related!
        // infile=0; outfile=1; 
    tab = token_alloc(tab); // malloc each token + each token[cmd]    
    while (tab->node[++i] && tkn_id < tab->tk_num)       
    {
        //expand_var ...   meta-char- safe-check execeptions 
        tab->node[i] = expand_vars(tab->node[i], -1, quotes, tab);  
        // printf("DEBUG/: split_all tab->node[id:%d] node{%s} \n", i, tab->node[i]);	    
        //expand_path ...         t->cmd[0] = "cmd" : t->cmd[1] = "cmd args etype" 
        tab->node[i] = expand_path(tab->node[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));
        // printf("DEBUG: split_all tab->token->path == {%s} \n", tab->token->path);
    }
    tab = div_token(tab, "<|>"); // padd endtype + set token 
    return (tab); 
}

static t_table  *parse_args(t_table *tab)
{

    int is_exit;
    t_token *token;

    is_exit = 0;
    token = tab->token;
    tab->token->id = 1;
    // tab = token_alloc(tab); // malloc each token + each token[cmd]    
    printf("DEBUG: into... parse\n");
    tab = redir_type(tab); // *refs[id] tk_num [end_pos] == tk_len
        // printf("DEBUG:  tk_num    __%d__ ...\n", tab->tk_num);        
        // printf("DEBUG:  t->tk->id __%d__ ...\n", tab->token->id); 
        // printf("DEBUG:  t->refs   __%d__ ...\n", tab->refs[tab->token->id]); 
    tab = split_all(tab);         
    tab->token->id = 1;
    printf("DEBUG:: parse: t->id[%d] OF [%d] << token...\n", tab->token->id, tab->tk_num);
    
    // token = get_token(tab, tab->token, tab->token->id);
    while (tab->token->id <= tab->tk_num)
    {
        tab->token = token;
        g_status = builtins_handler(tab, tab->token);
        waitpid(-1, &g_status, 0);
        
        if (!is_exit && g_status == 13)
            g_status = 0;
        if (g_status > 255)
            g_status = g_status / 255;
        tab->token->id++;     
    }
          
    if (tab->cmds && is_exit)
    {
        tab->tk_num = 0;
        tab->refs = NULL;
        ft_mx_free(tab->cmds);
        ft_mx_free(&tab->node);
        free_cont(tab->token);
        // ft_mx_free(&tab->token->cmd);
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
    if (!tab)
        return ("");
    // parse
    tab = parse_args(tab);

    free(input);
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

    ls -lt -a| head -3|wc -w>>out.txt
    ls -lt>>popox.txt  

*/ 
}
