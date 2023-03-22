/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:03:50 by loadjou           #+#    #+#             */
/*   Updated: 2023/03/22 12:15:32 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/**
 * @brief 
 * 
 * @param env to setenv the old_pwd as env variable. 
 * @return char* old_pwd saved as soon as we got to call one of our builtins.
 */
static char	*cd_hyphen(char **env)
{
	char	*old_pwd;

	old_pwd = ms_getenv("OLDPWD", env, 1);
	if (old_pwd)
		return (old_pwd);
	ft_putstr_fd("Error while trying to get old_pwd\n", 2);
	return (0);
}
/**
 * @brief Get the cd path function check and compare cmd[1] to get the path
 * and cd into it.
 * 
 * @param cmd full given cmd ex: cd "./" 
 * @returns the path as const char* that will be given as param to chdir()
 */
/* "ls" "-l" */

static char	*get_cd_path(char **cmd, char **env)
{
	char	*path;

	path = NULL;
	if (!cmd[1] || ft_strcmp(cmd[1], "#") == 0 || ft_strcmp(cmd[1], "~") == 0)
		path = ms_getenv("HOME", env, 4);
	else if (ft_strcmp(cmd[1], "..") == 0)
		path = ft_strdup("..");
	else if (ft_strcmp(cmd[1], "/") == 0)
		path = ft_strdup("/");
	else
		path = ft_strdup(cmd[1]);
	return (path);
}

int	cd(char **cmd, char **env)
{
	char	*path;

	path = get_cd_path(cmd, env);
	if (path)
	{
		if (chdir(path) != 0)
		{
			printf("cd: no such file or directory: %s\n", path);
			return (0);
		}
		free(path);
	}
	else if (cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (0);
	}
	else
	{
		printf("Minishell: command not found: %s\n", cmd[0]);
		return (0);
	}
	return (1);
}
