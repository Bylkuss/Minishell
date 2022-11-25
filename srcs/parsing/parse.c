/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/24 20:47:37 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

//  //  //   moved to node...

// char	**fill_nodes(t_table *tab, int i)
    // {
    // 		// t_token	**token;
    // 			// t_list	*cmds[2];
    // 			// token = init_token()
    // 			// cmds[0] = NULL;
    // 			// char	**temp[2];

    // 			// temp[1] = get_trimmed(tab->cmds); /* malloc_machine twin part */
    // 	while (tab->cmds && i < tab->token_len)
    // 	{
    // 		// revert from list 
    // 			// need to set first arg => cmd 
    // 			// 			set last arg => endtype
    // 			//	middle arg (if so!) 	
    // 		// cmds[1] = ft_lstlast(cmds[0]);

    // 		if (i == 0 || (tab->cmds[i][0] == '|' && *tab->cmds[i + 1] && tab->cmds[i + 1][0]))
    // 		{
    // 			// i += args[i][0] == '|';
    // 			//	ft_lstadd_back(&cmds[0], ft_lstnew(mx_init()));		/* mx_start */
    // 			//	cmds[1] = ft_lstlast(cmds[0]);
    // 		}

    // 		// temp[0] = args;
    // 		// tab->token = token_params(tab);//, &i);
    // 			// token->cmd = cmds[1]->content;
    // 				// token->arg = *temp[1];
    // 				// token->endtype = cmds[1]->content;
    // 				// if (i < 0)
    // 				// 	return (stop_fill(cmds[0], args, temp[1]));
    // 				// if (!args[i])
    // 				// 	break ;
    // 	}
    // 	// ft_mx_free(&temp[1S
    // 	return (tab->node);
    // }
/*       char **args = tab->cmds  :  token chunk    */


static char **split_all(char **args, t_table *tab)  
{
    // char **aux;
    int i;                          //token->id 
    int quotes[2];

    i = -1;
    while (args && args[++i])       
    {
        //expand_var
        //  :: node_id[0]/node_id[len-1]                {(attr = null) if (len = 2)}
        //  :: token->[cmd][attr][end] ==>> token->[cmd=id[0]] [attr] [end=id[len-1]]
        args[i] = expand_vars(args[i], -1, quotes, tab);       
        //expand_path
        args[i] = expand_path(args[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));              
        //
        tab = div_token(args[i], "<|>", tab);         /* token divider */     
        // ft_mx_rpl(&args, aux, i);                           
        // i += ft_mx_len(aux) - 1;                          
        // ft_mx_free(&aux);                                 
    }
    return (args); 
}

static t_token *parse_args(t_table *tab)
{
    int i; 
    // int is_exit; // is_exit = 0;
    /*  args =>                              */
    char **args;
    args = tab->cmds;
    tab->cmds = split_all(tab->cmds, tab);  // split all >> tab->cmds 
    tab = fill_nodes(tab, tab->cmds);                  // 
    /*                   args breaker => cmd_token*/ 
    if (!tab->node)
        return (tab->token);
                    //    args breaker => cmd_token*/ 
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
    // char **test;
    // char spc;
    int len;

    len = 0;
    // spc = 32;
    // test = NULL;
    if (!out)
    {
        printf("exit\n");
        return (NULL);
    }
    if (out[0] != '\0')
        add_history(out);
    //
    tab->cmds = space_split(out, " ");  
    mx_display_tab(tab->cmds);
                //input divided by space  **tab    
                // if (tab)
                //     mx_display_tab(tab->cmds);
    // free(out);
    if (!tab)
        return (NULL);
    // tab->token  ... 
    tab->token = parse_args(tab);    

    // if (tab && tab->token)
    //     display_tkn(tab);
        // tab->attr = ;
    /*
    if (tab && tab->token)
        display_tkn(tab);

       token need to be ID _cmd, _attr, _end   
    */

    // if (tab && tab->cmds && tab->token && tab->token_len > 0)
    // {
    //     // mx_display_tab(tab->cmds);
    //     /*
    //     // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
    //     //  - 1], p->envp, 1);                                    
    //         //     ft_lstclear(&p->cmds, free_content);
    //         */
    // }
    return (tab); 
}
//

/* void *check_args(char *out, t_table tab)  // maybe needed to return (tab)
    // {
    //     char    **arr;
        
    //     if (!out)
    //     {
    //         printf("exit\n");
    //         return (NULL);
    //     }
    //     if (out[0] != '\0')
    //         add_history(out);
    //     //
    //     tab->cmds = space_split(out, " ");  
    //                 //input divided by space  **tab    
    //                 // if (tab)
    //                 //     mx_display_tab(tab->cmds);
    //     // free(out);
    //     if (!tab)
    //         return ("");
    //     // tab->token  ... 
    //     tab->token = parse_args(tab);    
    //     if (tab && tab->token)
    //         tab->attr = ; 
    //     if (p && p->cmds && m && m->full_cmd && ft_lstsize(p->cmds) == 1)    
    //     {
    //         p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
    //          - 1], p->envp, 1);                    
    //             //     ft_lstclear(&p->cmds, free_content);
    //     }
    //     // mx_display_tkn(token);
    //     return (p); 
// }*/

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
