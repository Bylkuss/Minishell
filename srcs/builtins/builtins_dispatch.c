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

int    builtins(t_table *tab, t_list *cmdl, int *is_exit)
{
    // char *input;
    // char **envp;
    char **aux;
    int i;

    // envp = tab->envp;
    while (cmdl)
    {
        printf("\nDEBUG: @_@_@_@ Builtins ::: :::[id:%d] ::: \n", tab->node->id);//t->path { %s }\n", node->path); 	//len[%d]", l);
        aux = ((t_node *)cmdl->content)->cmd;
        i = 0;
        if (aux)
            i = ft_strlen(*aux);
        if (aux && !ft_strncmp(*aux, "exit", i) && i == 4)
            exit_builtin(aux);
        else if(!cmdl->next && aux && !ft_strncmp(*aux, "cd", i) && i == 2)
            g_status = cd(aux, tab->envp);
        else if(!cmdl->next && aux && !ft_strncmp(*aux, "export", i) && i == 6)
            g_status = ms_export(aux , tab->envp);
                // else if(ft_strnstr(*node->cmd, "echo", 10))
                //     g_status = echo(node->cmd);
                // else if (ft_strnstr(*node->cmd, "pwd", 10))
                //     g_status = pwd();
        else if(!cmdl->next && aux && !ft_strncmp(*aux, "unset", i) && i == 5)
        {
            if(unset((aux), tab->envp) == 0)
                printf("No such variable\n");
        } 
        else if(!ft_strncmp(*aux, "env", i) && i == 3)
            env(tab->envp);
        else 
        {
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            printf("\nDEBUG:::___ ___  builtin => execmd___ ___ ___\n");
            execmd(tab, cmdl);
        }
        cmdl = cmdl->next;
    }
    return (g_status);
}


