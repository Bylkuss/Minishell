/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/01 04:07:15 by gehebert         ###   ########.fr       */
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
    cmd = ft_mx_dup(tab->node); 
    n = ft_mx_len(cmd);   
    // printf  ("DEBUG: node_num[%d]\n", n);
    // printf  ("DEBUG: node_num[%d]::value{%s}\n", n,cmd[n-1]);
    // if(n > 1) 
    tab->token->id = 1;
    ref[tab->token->id] = 0; 
    while (id++ < (n - 1))
    {
        tab->token->id = tab->tk_num;        // printf  ("DEBUG: id[%d] :: tk_num[%d]\n", id, tab->tk_num);
        if (cmd[id] && (id + 1) < (n - 1))
        {
            if (*cmd[id] == '<' && (cmd + 1)  && *cmd[id + 1] == '<')
                tab->token->endtype = 5;// printf  ("DEBUG: id[%d] ::REDIR::{%s}:: tk_num[%d]\n", id, cmd[id], tab->tk_num);//tab->tk_num++; 
            else if (*cmd[id] == '<')
                tab->token->endtype = 4;//printf  ("DEBUG: id[%d]::REDIR::{%s}:: tk_num[%d]\n", id, cmd[id], tab->tk_num);//tab->tk_num++;  
            else if (*cmd[id] == '>' && (cmd + 1)  && *cmd[id + 1] == '>')
                tab->token->endtype = 3;//printf  ("DEBUG: id[%d] ::REDIR::{%s}:: tk_num[%d]\n", id, cmd[id], tab->tk_num);//tab->tk_num++;  
            else if (*cmd[id] == '>')
                tab->token->endtype = 2;// printf  ("DEBUG: id[%d] ::REDIR::{%s}:: tk_num[%d]\n", id, cmd[id], tab->tk_num);//tab->tk_num++;  
            else if (*cmd[id] == '|')
            {
                tab->tk_num++;  
                tab->token->endtype = 1;
            }
            ref[tab->token->id] = id;                // printf  ("DEBUG: id[%d] ::REDIR::{%d}:: tk_num[%d]\n", id, tab->token->endtype, tab->tk_num);
            // if (tab->token->endtype != -1)
            //     printf  ("DEBUG: REDIR_ NEW_REF::TK_ID[%d]== ETYPE(pos)REF[%d]\n", tab->token->id, ref[tab->token->id]);
            
        }
        // tab->token->endtype = -1;
    }
    if (tab->token->endtype == -1)
    {
        ref[tab->token->id] = id-1;
        tab->token->endtype = 0;
    }
    printf  ("DEBUG: REDIR_ ->endtype [%d]\n", tab->token->endtype);
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
    while (tab->node[++i] && tkn_id <= tab->tk_num)       
    {
        //expand_var ...   meta-char- safe-check execeptions 
        tab->node[i] = expand_vars(tab->node[i], -1, quotes, tab);  
        	// printf("DEBUG/: split_all tab->node[id:%d] node{%s} \n", i, tab->node[i]);	
            
        //expand_path ...         t->cmd[0] = "cmd" : t->cmd[1] = "cmd args etype" 
        tab->node[i] = expand_path(tab->node[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));

        //must be token->path here
            // could add token->full here-now ... 
            //  token->cmd[0] ==> char *:"cmd"
            //  token->cmd[1] ==> char *:"full cmd arg etype" ...etype will fall later

            // printf("DEBUG: split_all tab->token->path == {%s} \n", tab->token->path);
    }
    tab = div_token(tab, "<|>"); // padd endtype + set token 
    // tab->token = get_token(tab, tab->token, tkn_id);
    return (tab); 
}

static t_token *set_token(t_table *tab)
{
    
    int id;
    int len;
    t_token *t;

    t = tab->token;
    id = tab->token->id;
            /// set token >> malloc each >> 
                // printf("ok ici SET_T:: tk_num [%d]\n", tab->tk_num);
                // printf("ok ici SET_T:: token->id [%d]\n", tab->token->id);
        // if (tab->token->id == 0)
        //     tab->token->id = 1;
        if (t->id == 0)
            t->id = 1;
             // else
            // tab->token->id++;
            // tab->token->cmd = ft_split(tab->token->cmd[tab->token->id], ' ');
            // ft_split(*tab->token->cmd, ' ');
            // tab->token->lead = ft_strdup(lead[0]);

				// mx_display_tab(tab->token->cmd);
				// printf("DEBUG: token_fill path {%s} \n", tab->node[i + 1]);	
				// printf("DEBUG: token->full __%s__\n", tab->token->full);
				// printf("DEBUG: token->ofile {%s} \n\n", tab->token->ofile);

    	    // setting t->ofile value OUTFILE 1 & 2
            // len = ft_mx_len(tab->token->cmd[]);
        t->endtype = set_endtype(tab,tab->node[tab->refs[id]]);
		printf("DEBUG:  SET_T:: token->id[%d] cmd{%s} \n", id, t->cmd[id]);
        printf("DEBUG:  SET_T:: t->etype [%d]  \n", t->endtype);
        
        if (t->endtype == 2 )// || tab->token->endtype == 3)
            t = get_outfile1(t, tab);
        else if (t->endtype == 3)
            t = get_outfile2(t, tab);
        else if (t->endtype == 4)
            t = get_infile1(t, tab);
        else if (t->endtype == 5)
            t = get_infile2(t, tab);   
			// else if (tab->token->endtype == 0)        
        tab->token = t;    
    return(tab->token);
}

static t_table  *parse_args(t_table *tab)
{

    int is_exit;
    // int tk_id;
    t_token *token;

    token = tab->token;
    is_exit = 0;
    tab->token->id = 1;
    printf("DEBUG: into... parse\n");
    tab = redir_type(tab); // *refs[id] tk_num [end_pos] == tk_len
    // printf("DEBUG:  tk_num    __%d__ ...\n", tab->tk_num);        
    // printf("DEBUG:  t->tk->id __%d__ ...\n", tab->token->id); 
    // printf("DEBUG:  t->refs   __%d__ ...\n", tab->refs[tab->token->id]); 

      //
        ///
        // tab = token_alloc(tab); // malloc each token + each token[cmd]    
        // tab = div_token(tab, "<|>"); // padd endtype + set token 
        //
        ///
        //  OK NOW HERE : tab->cmds[id] shld have every node set... 
        //  SO IF INFILE2 GET ENDTYPE at the begening ... // tab->token = get_token(tab, tab->token, tkn_id);
        ///
    //
    tab = split_all(tab);         
       /*  tab->node [*str]  sep.space. node -ID.less
            tab >> tab->token-> ... arg-set value ...TBD            
            i = ft_lstsize(tab->cmds);     */
           // g_status = builtin(p, p->cmds, &is_exit, 0);       
            // if (tab->token->endtype >= 0)
        // tab->token = get_token(tab, tab->token, tab->token->id);
       // while (tab->token->endtype <= 0)
    tab->token->id = 1;
    printf("DEBUG:: parse: t->id[%d] OF [%d] << token...\n", tab->token->id, tab->tk_num);
    
    tab->token = get_token(tab, tab->token, tab->token->id);
    while (tab->token->id <= tab->tk_num)
    {
        token = tab->token;
        // printf("\nDEBUG: parse_ #token[%d] . . .\n\n", tab->token->id);     
        if(tab->token->id < tab->tk_num)
            tab->token = set_token(tab);

        // first get token 
            // all of them 
            // then do it
            // free conte   nt...

            // set a token for each endtype
            //
            // tab->token->id++;
            //  // fill is form ... t->cmd** t->path t->endtype
            //  // 
        g_status = is_builtin(tab->token);       
        if (g_status == 1)
            printf("\nDEBUG : is_builtin (%d)::{%s}\n", is_builtin(token), *token->cmd);     
        g_status = builtins_handler(tab, tab->token, token->id);
        
        tab->token->id++;
        token->path = NULL;
        free_cont(token);
        // token->id++;

        // {
        
            // if (tab->token->endtype == 0)
            // {
            //     execmd(tab, tab->token, tk_id);

            // }
            //     tab->token->tk_len--;
            // else
            // printf("DEBUG : g_status << {%d} >>::\n", g_status);     

            // free_cont(tab->token, tk_id);
            // tk_id--;
            // tab->token->id++;
            // if (tk_id > 0 )//|| tab->tk_num == 0)
                // tab->token = get_token(tab, tab->token, 1);
            // tab->tk_num--;
            //     break;

    }
   
    while (tab->token->id <= tab->tk_num)
        waitpid(-1, &g_status, 0);
        //
    if (!is_exit && g_status == 13)
        g_status = 0;

    if (g_status > 255)
        g_status = g_status / 255;
    if (tab->cmds && is_exit)
    {
        // tab->tk_num = 0;
        ft_mx_free(tab->cmds);
        ft_mx_free(&tab->node);
        free_cont(tab->token);
        ft_mx_free(&tab->token->cmd);
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
