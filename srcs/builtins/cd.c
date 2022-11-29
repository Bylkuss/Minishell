/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:03:50 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/29 10:55:57 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
char	*get_root(char **env)
{
    char *user;
	int	i;

    i = 0;
    while(env[i])
    {
        user = ft_strnstr(env[i], "USER=", 5);
        if(user)
            return (&user[5]);
        i++;
    }
    return (NULL);
}
*/

// (void)cmd;
// char *pwd;
// char path[2000];
// pwd = getwd(path);
// printf("%s\n", pwd);

void	cd(char **cmd, char **env)
{
	if(!cmd[1] || !ft_strcmp(cmd[1], "#") || !ft_strcmp(cmd[1], "~"))
		chdir(ms_getenv("HOME", env, 4));
	else if (ft_strcmp(cmd[1], "..") == 0)
		chdir("..");
	else if (ft_strcmp(cmd[1], "/") == 0)
		chdir("/");
	/* 
    else if(ft_strcmp(cmd[1], "-") == 0) 
    else if(ft_strcmp(cmd[1], "\\") == 0)
    ***************???????**************
    */
	else
		chdir(cmd[1]);
}
