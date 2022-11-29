/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/28 21:13:04 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

// char *node_check(char *input, char meta)
// {
//     char *tmp;
//     int i[2];
//     int j;

//     i[0] = 0;
//     i[1] = 0;
//     j = 0; 
//     j = ft_strlen(input);
//     while(input && *input != '\0')
//     {
//         //strchr meta_input get ptr
//         i[0] = ft_strchr_i((const char *)input, meta);
//         if (i[0])
//         {
//             // substr ptr meta input-a input-b
//             tmp = ft_substr((const char *)input, (i[0] - 1), (j - i[0])); 
//             //strchr meta input-b get ptr 
            
            
//         // substr ptr meta input -b input-c
//         // strjoin -a + " " + -b + " " + -c
//         }
//     }
//     // strchr(me
//     return(input);

// }

/*       char **args = tab->cmds  :  token chunk    */
static t_table *split_all(char **args, t_table *tab)  
{
    char **nodes;
    int i;              //token->id 
    int quotes[2];

    i = -1;
    printf("DEBUG : into... split all\n");
    while (args && args[++i])       
    {
        // args = tab->cmds[id]
            //        :: node_id[0]/node_id[len-1] {(attr = null) if (len = 2)}
            //        :: token->[cmd][attr][end] ==>> token->[cmd=id[0]] [attr] [end=id[len-1]] */
        args[i] = expand_vars(args[i], -1, quotes, tab);  
        //expand_var ...  
        args[i] = expand_path(args[i], -1, quotes, ms_getenv("HOME", tab->envp, 4));              
        //expand_path ...
        nodes = div_token(args[i], "<|>", tab); 
        // mx_ext (nodes(len + 1))
        // ft_mx_ext(args, )
                //
        // mx_rpl (arg , node)
        // free node


        //token divider  ...
            // watch out :: splt_all >> tab-cmds 
            //           :: tab->token <<
    }
    // mx_display_tab(args);
    return (tab); 
}

t_table  *parse_args(t_table *tab)
{
    int i;   
        // int is_exit; // is_exit = 0;
    i = 0;
    printf("DEBUG: parse...\n");
    //
    tab = split_all(tab->cmds[0], tab);
    //    tab >> tab->node  ::  substr( tab->cmds >> endtype ) 
    tab = token_nodes(tab);  
    //node_token == token_builder ...  use of mx cmds[id] = tab->node
    /*   tab->node [*str]  sep.space. node -ID.less
        //    tab >> tab->token-> ... arg-set value ...TBD            
        //  
        // if (tab->token)
        //     display_tkn(tab);
   
        if (!tab->node)
            return (tab->token);
                    //    args breaker => cmd_token

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
    return (tab);
}

t_table  *check_args(char *input, t_table *tab)  
{
    if (!input)
    {
        printf("exit\n");
        return (NULL);
    }
    if (input[0] != '\0')
        add_history(input);
    // meta_chk >> insert space in before/after it if neede
    // input = node_check(input, "|");

    //  input divided by space ::    
    //      error space split need to check if no-space-too
    //
        
    tab->node = space_split((const char *)input, " ");
    
    // if (tab->node)
    // {
    //     *tab->cmds = node_check(tab->node, "|");

    // }
        // printf("\nOK TEST INPUT :: :: END\n");   
            // mx_display_tab(tab->cmds);
            // display_tkn(tab);
            // len = ft_mx_len(tab->node);
            // printf("\n%d :::\n", len);
            // mx_display_tab(tab->cmds);
            // return (tab);
    // if (tab->cmds[0])
    //     printf("DEBUG : into... check_arg\n");
    printf("GO_GO_GO>>PARSE\n");    // DEBUG
    tab = parse_args(tab);    
        // exit(0);
        // if (tab->cmds && tab->tk_num > 0)
        // else
        //     return (NULL);
    /*
            if (tab && tab->token)
                display_tkn(tab);

            token need to be ID _cmd, _attr, _end   
        */
        /*
            if (tab && tab->cmds && tab->token && tab->tk_num > 0)
            {
                // mx_display_tab(tab->cmds);
                // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
                //  - 1], p->envp, 1);                                    
                    //     ft_lstclear(&p->cmds, free_content);
    }

    */
    // free(input);
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
