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


static char **split_all(char **args, t_dot *p)  /* token chunk*/
{
    char **aux;
    int i;
    int quotes[2];

    (void) p;
    i = -1;
    while (args && args[++i])
    {
        args[i] = expand_vars(args[i], -1, quotes, p);       
        args[i] = expand_path(args[i], -1, quotes, ms_getenv("HOME", p->envp, 4));              
        aux = div_token(args[i], "<|>");         /* token divider */     
        ft_mx_rpl(&args, aux, i);                           
        i += ft_mx_len(aux) - 1;                          
        ft_mx_free(&aux);                                 
    }
    return (args); 
}

static void *parse_args(char **args, t_dot *p)
{
    // int is_exit;
    // t_token	*token;
    int i;

    // is_exit = 0;
    p->cmds = fill_nodes(split_all(args, p), -1);    /* args breaker => cmd_token*/ 
    if (!p->cmds)
        return (p);
  
    i = ft_lstsize(p->cmds);
    // g_status = builtin(p, p->cmds, &is_exit, 0);             
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
    return (p);
}

void *check_args(char *out, t_dot *p) 
{
    char    **tab;
    // t_token	*token = NULL;
    t_mini  *m;
    
    if (!out)
    {
        printf("exit\n");
        return (NULL);
    }
    if (out[0] != '\0')
        add_history(out);                                 
    tab = subsplit(out, " ");           //input divided by space  **tab    
    // mx_display_tab(tab);
    free(out);
    if (!tab)
        return ("");
    p = parse_args(tab, p);     
    // token = init_token(p); 
    // mx_display_tab(token->table);
    // mx_display_str(token->cmd);
    if (p && p->cmds)
        m = p->cmds->content;
    if (p && p->cmds && m && m->full_cmd && ft_lstsize(p->cmds) == 1)
        p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd) - 1],\
            p->envp, 1);                                  
    // if (p->cmds->content)
    // {
    //     mx_display(p);
    //     exit(g_status);
    // }
    //     ft_lstclear(&p->cmds, free_content);
    return (p); 
}

/*
from check.c
    check_args  => take input to be space_split to build table command
    subsplit    => will do that space_split into a tab **       ==> subsplit.c
    parse_args  => call fill_node  return *p (list-> p.cmds)    ==> nodes.c
    split_all   =>  token's alternate end if it's not! 
                    div_token  ('<','>','|')                    ==> divide.c
                    expand_vars & expand_path                   ==> expand.c
    *** so in my mind a token is : CMD + ARG + END 
    *** in fact ARG is facultative
*/
