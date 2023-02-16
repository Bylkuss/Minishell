/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:54:28 by bylkus            #+#    #+#             */
/*   Updated: 2023/02/15 22:10:57 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

int is_builtin(t_node *t)
{
    int l;
    int id;
    
    id = 0; 
    if (!(t->cmd[0]))
		return (0);
	if (t->cmd && ft_strchr(*t->cmd, '/') || (t->path && ft_strchr(t->path, '/')))
		return (0);
	l = ft_strlen(*t->cmd);
	if (!ft_strncmp(*t->cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*t->cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*t->cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*t->cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*t->cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*t->cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*t->cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}

int    exit_builtin(char **cmd, int *is_exit)
{
    int exiit;// = 0;
    int i = 0;

    exiit = *is_exit;
    if(cmd[1] && !cmd[2])
    {
        while(cmd[1][i])
        {
            if(!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
                error_msg("exit: numeric argument required\n", 255);
            i++;                
        }
        exiit = ft_atoi(cmd[1]);
    }
    // exit(exiit);
    return (exiit);
}

// int    exit_builtin(t_node *node, int *is_exit)
    // {
    //     int exiit;
    //     int i;
    //     char **cmd;

    //     exiit = 0;
    //     i = 0;
    //     cmd = node->cmd;
    //     if(cmd[1] && !cmd[2])
    //     {
    //         while(cmd[1][i])
    //         {
    //             if(!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
    //                 error_msg("exit: numeric argument required\n", 255);
    //             i++;                
    //         }
    //         exiit = ft_atoi(cmd[1]);
    //     }
    //     exit(exiit);
// }



int    builtins(t_table *tab,  int *is_exit)
{
    t_node  *node;
    char    **arg;
    int     l;
    char     *input;



    node = tab->node;

    while(node->id <= tab->nods)
    {
        node = get_node(tab, node, node->id);

        printf("\nDEBUG: Builtins:: chk_bltn ::[id:%d] \n", node->id);//t->path { %s }\n", node->path); 	//len[%d]", l);
        arg = node->cmd;
        l = 0;
        input = *node->cmd;
        tab->envp = save_old_pwd(tab->envp);    
        if (arg)
            l = ft_strlen(*arg);
        
        if (arg && !ft_strncmp(*arg, "exit", l) && l == 4)
            g_status = exit_builtin(node->cmd, is_exit);
        else if(ft_strnstr(input, "echo", 10))
            g_status = echo(ft_split(input, ' '));
        else if (ft_strnstr(input, "pwd", 10))
            g_status = pwd();
        else if(ft_strnstr(input, "cd", 10))
            g_status = cd(ft_split(input, ' '), tab->envp);
        else if(ft_strnstr(input, "export", 10))
            g_status = ms_export(ft_split(input, ' ') , tab->envp);
        else if(ft_strnstr(input, "unset", 10))
        {
            if(unset(ft_split(input, ' '), tab->envp) == 0)
                printf("No such variable\n");
        } 
        else if(ft_strnstr(input, "env", 5))
            env(tab->envp);
        else 
        {
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            execmd(tab, node);
        }
        node->id++;

    }
    return (g_status);
}

// void    builtins_handler(char *input, char **envp)

// int    builtins_handler(t_table *tab, t_node *node)
// {
//     char *input;
//     char **envp;

//     // int i = 0;
//     // envp = tab->envp;
//      printf("\nDEBUG: Builtins:: chk_bltn ::[id:%d] \n", node->id);//t->path { %s }\n", node->path); 	//len[%d]", l);
//     input = *node->cmd;
//     envp = save_old_pwd(envp);    
//     if (ft_strnstr(input, "exit", 5))
//         exit_builtin(ft_split(input, ' '));
//     else if(ft_strnstr(input, "cd", 10))
//         g_status = cd(ft_split(input, ' '), envp);
//     else if(ft_strnstr(input, "export", 10))
//         g_status = ms_export(ft_split(input, ' ') , envp);
//     else if(ft_strnstr(input, "unset", 10))
//     {
//         if(unset(ft_split(input, ' '), envp) == 0)
//             printf("No such variable\n");
//     } 
//     else if(ft_strnstr(input, "env", 5))
//         env(envp);
//     else 
//     {
//         signal(SIGINT, SIG_IGN);
//         signal(SIGQUIT, SIG_IGN);
//         execmd(tab, node);
        
//     }
//     return (g_status);
//     // else if(ft_strnstr(input, "echo", 10))
//     //     g_status = echo(ft_split(input, ' '));
//     // else if (ft_strnstr(input, "pwd", 10))
//     //     g_status = pwd();
// }


