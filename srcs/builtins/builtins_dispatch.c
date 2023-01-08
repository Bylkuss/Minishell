/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:54:28 by bylkus            #+#    #+#             */
/*   Updated: 2022/12/20 13:51:54 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(t_token *t)
{
    int l;

    if (!t->cmd[0])
		return (0);
	if (t->cmd && ft_strchr(*t->cmd, '/'))// || (n->path && ft_strchr(n->path, '/')))
		return (0);
	l = ft_strlen(t->cmd[0]);
	if (!ft_strncmp(t->cmd[0], "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(t->cmd[0], "env", l) && l == 3)
		return (1);
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
    int exiit = ft_atoi(cmd[1]);
    exit(exiit);
}


void    builtins_handler(char *input, char **envp)
{
    // envp = save_old_pwd(envp);    
    if(ft_strnstr(input, "cd", 10))
            cd(ft_split(input, ' '), envp);
    else if (ft_strnstr(input, "pwd", 10))
        pwd();
    else if(ft_strnstr(input, "echo", 10))
        echo(ft_split(input, ' '));
    else if(ft_strnstr(input, "env", 5))
        env(envp);
    else if(ft_strnstr(input, "unset", 10))
        unset(ft_split(input, ' ') , envp);
    // else if(ft_strnstr(input, "export", 10))
    //     export(ft_split(input, ' ') , envp);
    else if (ft_strnstr(input, "ls", 5))
        execve("/usr/bin/ls", ft_split(input, ' '), envp);
    else if (ft_strnstr(input, "exit", 5))
        exit_builtin(ft_split(input, ' '));
}