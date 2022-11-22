/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/17 14:18:58 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;


/*       char **args = tab->cmds  :  token chunk    */
static char **split_all(char **args, t_table *tab)  
{
    // char **aux;
    int i;                          //token->id 
    int quotes[2];

    i = -1;
    while (args && args[++i])       
    {
        /*// args = tab->cmds[id]
        //  :: node_id[0]/node_id[len-1]                {(attr = null) if (len = 2)}
        //  :: token->[cmd][attr][end] ==>> token->[cmd=id[0]] [attr] [end=id[len-1]] */
        args[i] = expand_vars(args[i], -1, quotes, tab);    //expand_var   //expand_path;
        args[i] = expand_path(args[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));              
        tab = div_token(args[i], "<|>", tab);               //token divider 
        // i += ft_mx_len(aux) - 1;  // ft_mx_rpl(&args, aux, i);                           
        // ft_mx_free(&aux);                                 
    }
    return (args); 
}

static t_token *parse_args(t_table *tab)
{
    int i;   // int is_exit; // is_exit = 0;
    char **args;

    args = tab->cmds;                   //  args =>        
    //
    tab->cmds = split_all(args, tab);   //  split_arg token_chunk _ID
    //
    tab->node = fill_nodes(tab, tab->token_len);  //split_arg 
    //
    /*
    if (!tab->node)
        return (tab->token);
                       args breaker => cmd_token*/ 
    /*   tab->node [*str]  sep.space. node -ID.less

        // tab->
        // i = ft_lstsize(tab->cmds);
        // g_status = builtin(p, p->cmds, &is_exit, 0);             
    */
    i = 0;
    while (i-- > 0)
        waitpid(-1, &g_status, 0);
    if (g_status > 255)
        g_status = g_status / 255;
    /*
    // if (!is_exit && &g_status == 13)
    //     g_status = 0;
    // if (args && is_exit)
        // {
        //     ft_lstclear(&p->cmds, free_content);
        //     return (NULL);
    // }
    */
    return (tab->token);
}

t_table  *check_args(char *out, t_table *tab)  
{
        
    if (!out)
    {
        printf("exit\n");
        return (NULL);
    }
    if (out[0] != '\0')
        add_history(out);
    //
    tab->cmds = space_split(out, " ");   //input divided by space  **tab    
    
    tab->token_len = ft_mx_len(tab->cmds);
    if (tab->token_len)
    {
        printf("\n%d :::\n", tab->token_len);
        exit(0);
        return (NULL);
    }
    if (tab->cmds && tab->token_len > 0)
        mx_display_tab(tab->cmds);
    else
        return (NULL);
    tab->token = parse_args(tab);    
    /*
    if (tab && tab->token)
        display_tkn(tab);

       token need to be ID _cmd, _attr, _end   
    */

    /*
    if (tab && tab->cmds && tab->token && tab->token_len > 0)
    {
        // mx_display_tab(tab->cmds);
        // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
        //  - 1], p->envp, 1);                                    
            //     ft_lstclear(&p->cmds, free_content);
    }

    */
    free(out);
    return (tab); 
}

/*
from check.c
    check_args  => take input to be space_split to build table command
    space_split    => will do that space_split into a tab **       ==> space_split.c
    parse_args  => call fill_node  return *p (list-> p.cmds)    ==> nodes.c
    split_all   =>  token's alternate end if it's not! 
                    div_token  ('<','>','|')                    ==> divide.c
                    expand_vars & expand_path                   ==> expand.c
    *** so in my mind a token is : CMD + ARG + END 
    *** in fact ARG is facultative
*/
