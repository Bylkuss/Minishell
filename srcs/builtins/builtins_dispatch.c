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

void    exit_builtin(char **cmd)//, int *is_exit)
{
    int exiit = 0;
    int i = 0;

    // exiit = *is_exit;
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
    exit(exiit);
    // return (exiit);
}

// int    exit_builtin(t_table *tab, int *is_exit)
// {
//     char ** cmd;
//     int i = 0;

//     cmd = tab->node->cmd;
//     *is_exit = 1;
//     if(cmd[1] && !cmd[2])
//     {
//         while(cmd[1][i])
//         {
//             if(!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
//                 error_msg("exit: numeric argument required\n", 255);
//             i++;                
//         }
//         *is_exit = ft_atoi(cmd[1]);
//         if (*is_exit == -1)
//             return (255);
//     }
//     else 
//     {
//         *is_exit = 0;
//         return (1);
//     }
//     // exit(exiit);
//     return (g_status);
// }

int    builtins_handler(t_table *tab, t_node *node)
{
    // char *input;
    char **envp;

    // int i = 0;
    // envp = tab->envp;
    while(tab->node->id <= tab->nods)
    {
        printf("\nDEBUG: @_@_@_@ Builtins ::: :::[id:%d] ::: \n", node->id);//t->path { %s }\n", node->path); 	//len[%d]", l);
        tab->node = get_node(tab, node, node->id);

        // input = *node->cmd;
        envp = save_old_pwd(envp);    
        if (ft_strnstr(*node->cmd, "exit", 5))
            exit_builtin(tab->node->cmd);
        else if(ft_strnstr(*node->cmd, "cd", 10))
            g_status = cd(node->cmd, envp);
        else if(ft_strnstr(*node->cmd, "export", 10))
            g_status = ms_export(node->cmd , envp);
                // else if(ft_strnstr(*node->cmd, "echo", 10))
                //     g_status = echo(node->cmd);
                // else if (ft_strnstr(*node->cmd, "pwd", 10))
                //     g_status = pwd();
        else if(ft_strnstr(*node->cmd, "unset", 10))
        {
            if(unset((node->cmd), envp) == 0)
                printf("No such variable\n");
        } 
        else if(ft_strnstr(*node->cmd, "env", 5))
            env(envp);
        else 
        {
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            printf("\nDEBUG:::___ ___  builtin => execmd___ ___ ___\n");
            execmd(tab, node);
            
        }
        tab->node->id++;
    }
    return (g_status);
}


