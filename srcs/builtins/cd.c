/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:03:50 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/30 10:53:42 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
