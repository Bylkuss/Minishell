/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:03:50 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/19 14:18:38 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/**
 * @brief 
 * 
 * @param env to setenv the old_pwd as env variable. 
 * @return char* old_pwd saved as soon as we got to call one of our builtins.
 */
static char *cd_hyphen(char **env)
{
	char *old_pwd;
    // Change to the previous working directory
    old_pwd = ms_getenv("OLDPWD", env, 1);
	if(old_pwd)
		return old_pwd;
	ft_putstr_fd("Error while trying to get old_pwd\n", 2);
	return 0;
}
/**
 * @brief Get the cd path function check and compare cmd[1] to get the path
 * and cd into it.
 * 
 * @param cmd full given cmd ex: cd "./" 
 * @returns the path as const char* that will be given as param to chdir()
 */
static const char *get_cd_path(char **cmd, char **env)
{
	char *path;
	
	path = NULL;
	if(!cmd[1] || ft_strcmp(cmd[1], "#") == 0 || ft_strcmp(cmd[1], "~") == 0)
		path = ms_getenv("HOME", env, 4);
	else if (ft_strcmp(cmd[1], "..") == 0)
		path = ft_strdup("..");
	else if (ft_strcmp(cmd[1], "/") == 0)
		path = ft_strdup("/");
	else if (ft_strcmp(cmd[1], "-") == 0)
		path = ft_strdup(cd_hyphen(env));
	else
		path = ft_strdup(cmd[1]);
	return path;
}

void	cd(char **cmd, char **env)
{
	const char *path;
	
	if(cmd[2])
		ft_putstr_fd("cd: too many arguments\n", 2);
	path = get_cd_path(cmd, env);
	if(path)
	{
		if(chdir(path) != 0)
			printf("cd: no such file or directory: %s\n", path);
		// free(path);
	}
	else
	{
		printf("Minishell: command not found: %s\n", cmd[0]);
		exit(2);
	}
}
