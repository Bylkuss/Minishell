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
                // printf("Bad args\n");
            i++;                
        }
        exiit = ft_atoi(cmd[1]);
    }
    exit(exiit);
}


void    builtins_handler(char *input, char **envp)
{
    int i = 0;
    // envp = save_old_pwd(envp);    
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
    else if (ft_strnstr(input, "ls", 5))
        execve("/bin/ls", ft_split(input, ' '), envp);
    else if (ft_strnstr(input, "exit", 5))
        exit_builtin(ft_split(input, ' '));
}




