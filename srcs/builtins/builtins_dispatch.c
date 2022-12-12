/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:54:28 by bylkus            #+#    #+#             */
/*   Updated: 2022/12/12 05:58:27 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exit_builtin(char **cmd)
{
    int exiit = ft_atoi(cmd[1]);
    exit(exiit);
}

void    builtins_handler(char *input, char **envp)
{
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