/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:12:07 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/08 10:34:28 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strcmp_c(char *s1, char *s2, char until)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != until)
		i++;
	return (s1[i] - s2[i]);
}

static int	ft_strlen_c(char *str, char until)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != until)
		i++;
	return (i);
}

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

char	**edit_env(char **envp, int pos)
{
	if(!envp)
		return NULL;
	while (envp && envp[pos + 1])
	{
		envp[pos] = envp[pos + 1];
		pos++;
	}
	envp[pos] = NULL;
	return (envp);
}
 
char *cmd_trimmed(char *envp)
{
	char *cmd;

	cmd = ft_substr(envp, 0, ft_strlen_c(envp, '='));
	if(!cmd || !envp)
		return NULL;
	return cmd;
}
 
int	unset(char **cmd, char **envp)
{
	int	i;
	char *cmd_trim;
	i = 0;
	if (!cmd[1] || cmd[2])
	{
		printf("Missmatch args nb\n");
		return (0);
	}
	while (envp[i])
	{
		cmd_trim = cmd_trimmed(envp[i]);
		if (ft_strcmp(cmd_trim, cmd[1]) == 0)
		{
			free(cmd_trim);
			envp = edit_env(envp, i);
			return (1);
		}
		free(cmd_trim);
		i++;
	}
	return (0);
}
