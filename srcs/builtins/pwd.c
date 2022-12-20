/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:00:00 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/20 13:40:22 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**save_old_pwd(char **envp)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd== NULL)
        perror("getcwd() error");
	// envp = ms_setenv("OLDPWD", cwd, envp, 1);
	return(envp);
}

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));//path));
}

