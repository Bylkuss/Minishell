/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:54:28 by bylkus            #+#    #+#             */
/*   Updated: 2023/01/11 12:18:08 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(t_token *t)
{
    int l;

    if (!t->cmd[0])
		return (0);
	if (t->cmd && ft_strchr(*t->cmd, '/') || (t->path && ft_strchr(t->path, '/')))
		return (0);
	l = ft_strlen(t->cmd[0]);
	if (!ft_strncmp(t->cmd[0], "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(t->cmd[0], "env", l) && l == 3)
		return (1);
    // if (!ft_strncmp(t->cmd[0], "ls", l) && l == 2)
	// 	return (1);
	if (!ft_strncmp(t->cmd[0], "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(t->cmd[0], "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(t->cmd[0], "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(t->cmd[0], "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(t->cmd[0], "exit", l) && l == 4)
		return (1);
	return (0);
}


void    exit_builtin(char **cmd)
{
    int exiit = 0;
    int i = 0;
    if(cmd[1] && !cmd[2])
    {
        while(cmd[1][i])
        {
            if(!ft_isdigit(cmd[1][i]))
                error_msg("Bads args\n", 255);
                // printf("Bad args\n");env
            i++;                
        }
        exiit = ft_atoi(cmd[1]);
    }
    exit(exiit);
}


// void    builtins_handler(char *input, char **envp)
int    builtins_handler(t_table *tab, t_token *token, int id)
{
    char *input;
    char **envp;
    int i = 0;
    // envp = tab->envp;
    // input = token->cmd[0];
    input = tab->cmds[id][0];
    envp = save_old_pwd(envp);    
    if(ft_strnstr(input, "cd", 10))
        i = cd(ft_split(input, ' '), envp);
    else if (ft_strnstr(input, "pwd", 10))
        i = pwd();
    else if(ft_strnstr(input, "echo", 10))
        i = echo(ft_split(input, ' '));
    else if(ft_strnstr(input, "env", 5))
        env(envp);
    else if(ft_strnstr(input, "unset", 10))
    {
        if(unset(ft_split(input, ' '), envp) == 0)
            printf("No such variable\n");
    } 
    else if(ft_strnstr(input, "export", 10))
        i = export(ft_split(input, ' ') , envp);
    // else if (ft_strnstr(input, "ls", 5))
    //     execve("/bin/ls", ft_split(input, ' '), envp);
    else if (ft_strnstr(input, "exit", 5))
        exit_builtin(ft_split(input, ' '));
    else 
    {
        // signal(SIGINT, SIG_IGN);
        // signal(SIGQUIT, SIG_IGN);
        execmd(tab, tab->token, id);
    }
    return (i);
}



// void    builtins_handler(t_table *tab, t_token *token, int id)
// {
//     char *input;
//     char **envp;

//     envp = tab->envp;
//     input = token->cmd[0];
//     // envp = save_old_pwd(envp);    
//     if(ft_strnstr(input, "cd", 10))
//             cd(ft_split(input, ' '), envp);
//     else if (ft_strnstr(input, "pwd", 10))
//         pwd();
//     else if(ft_strnstr(input, "echo", 10))
//         echo(ft_split(input, ' '));
//     else if(ft_strnstr(input, "env", 5))
//         env(envp);
//     else if(ft_strnstr(input, "unset", 10))
//         unset(ft_split(input, ' ') , envp);
//     // else if(ft_strnstr(input, "export", 10))
//     //     export(ft_split(input, ' ') , envp);
//     else if (ft_strnstr(input, "exit", 5))
//         exit_builtin(ft_split(input, ' '));
//     // else 
//     // {
//     //     signal(SIGINT, SIG_IGN);
//     //     signal(SIGQUIT, SIG_IGN);
//     //     execmd(tab, tab->token, id);
//     // }
// }
