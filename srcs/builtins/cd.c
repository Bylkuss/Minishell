/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:03:50 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/17 18:45:48 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
char *get_root(char **env)
{
    char *user;
    int i = 0;
    while(env[i])
    {
        user = ft_strnstr(env[i], "USER=", 5);
        if(user)
            return (&user[5]);
        i++;
    }
    return NULL;
}
*/

void    cd(char **cmd, char **env)
{
    // (void)cmd;
    // char *pwd;
    // char path[2000];
    // pwd = getwd(path);
    // printf("%s\n", pwd);
    
    if(ft_strcmp(cmd[1], "..") == 0)
        chdir("..");
    else if(ft_strcmp(cmd[1], "/") == 0)
        chdir("/");
    else if(ft_strcmp(cmd[1], "#") == 0 || ft_strcmp(cmd[1], "~") == 0 || !cmd[1])
        chdir(ms_getenv("HOME", env, 4));
    /* 
    else if(ft_strcmp(cmd[1], "-") == 0) 
    else if(ft_strcmp(cmd[1], "\\") == 0)
    ***************???????**************
    */
    else
        chdir(cmd[1]);
        
}

/*



static void	change_dir_to_path(char *path)
{
	char	*pwd;
	char	*error_msg;
	char	buffer[2048];

	pwd = getcwd(buffer, 2048);
	hashmap_insert("OLDPWD", pwd, g_minishell.env);
	if (chdir(path) != 0 && ft_strchr(path, '>') == NULL)
	{
		error_msg = ft_strjoin("cd: ", path);
		error_message(error_msg, strerror(errno), 1);
		free(error_msg);
		return ;
	}
	pwd = getcwd(buffer, 2048);
	hashmap_insert("PWD", pwd, g_minishell.env);
}

static void	change_dir_to_oldpwd(char *path)
{
	printf("%s\n", path);
	change_dir_to_path(path);
}

static void	change_dir_to_home(void)
{
	char	*path;

	path = ft_strdup(hashmap_search(g_minishell.env, "HOME"));
	if (path == NULL)
	{
		error_message("cd", NO_HOME, 1);
		free(path);
		return ;
	}
	change_dir_to_path(path);
	free(path);
}

void	cd(char	*path)
{
	char	*current_path;

	g_minishell.error_status = 0;
	if ((!path) || ft_strcmp(path, "~") == 0)
	{
		change_dir_to_home();
		return ;
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		current_path = ft_strdup(hashmap_search(g_minishell.env, "OLDPWD"));
		if (current_path == NULL)
		{
			error_message("cd", NO_OLDPWD, 1);
			return ;
		}
		change_dir_to_oldpwd(current_path);
	}
	else
	{
		current_path = ft_strdup(path);
		change_dir_to_path(current_path);
	}
	free(current_path);
}
*/