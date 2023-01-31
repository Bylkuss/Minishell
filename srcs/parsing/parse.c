/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/23 02:33:17 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;
/*
* etype spot endtype index (tk_len, tk_num)
*/
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
    tab->tk_num = 0;
    ref[tab->token->id] = 0; 
    printf  ("DEBUG: mx_len[%d]\n", n);
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
        }
    }
    printf  ("DEBUG: tk_num[%d]\n", tab->tk_num);

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

    // tab = div_token(tab, "<|>");

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
    
    tab->token = get_token(tab, tab->token, tkn_id);
    return (tab); 
}

static t_table  *parse_args(t_table *tab)
{
    // int i;    // i = 0;
    // int type_id;    // tk_id = 0;
    int is_exit;
    int tk_id;
    t_token *token;
    // char *set;
    // set = "<|>";

    token = tab->token;
    is_exit = 0;
    tab->token->id = 1;
    printf("DEBUG: into... parse\n");
    tab = token_etype(tab); // *refs[id] tk_num [end_pos] == tk_len
    printf("DEBUG: #tab->tk_num[%d] ...\n", tab->tk_num);//);//, tab->tk_num);             
    tab = token_nodes(tab); // malloc each token + each token[cmd]    
    tab = div_token(tab, "<|>"); // padd endtype + set token 
    tab = split_all(tab);         
        /*  tab->node [*str]  sep.space. node -ID.less
            tab >> tab->token-> ... arg-set value ...TBD            
            i = ft_lstsize(tab->cmds);     */
           // g_status = builtin(p, p->cmds, &is_exit, 0);       
    // if (tab->token->endtype >= 0)
    while (tab->token->endtype >= 0)
    {
        // first get token 
            // all of them 
            // then do it
            // free content...

            // set a token for each endtype
            //
            //  // fill is form ... t->cmd** t->path t->endtype
            //  // 
        tab->token = get_token(tab, tab->token,  token->id);
        g_status = is_builtin(tab->token);       
        if (g_status == 1)
            printf("\nDEBUG : is_builtin {%d}::\n", g_status);     
        builtins_handler(tab, tab->token, token->id);
            
                // {
        
            // if (tab->token->endtype == 0)
            // {
            //     execmd(tab, tab->token, tk_id);

            // }
        //     tab->token->tk_len--;
        // else
        // printf("DEBUG : g_status << {%d} >>::\n", g_status);     

        free_cont(tab->token, tk_id);
        tk_id--;
        // tab->token->id++;
        if (tk_id > 0 )//|| tab->tk_num == 0)
        // tab->tk_num--;
        printf("DEBUG: #token[%d] . . .\n", tab->tk_num);     
        //     break;

   }
   
    tk_id = tab->tk_num;
    while (tk_id-- > 0)
        waitpid(-1, &g_status, 0);
        //
    if (!is_exit && g_status == 13)
        g_status = 0;

    if (g_status > 255)
        g_status = g_status / 255;
    if (tab->cmds && is_exit)
    {
        ft_mx_free(tab->cmds);
        ft_mx_free(&tab->node);
        free_cont(tab->token,tk_id);
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
