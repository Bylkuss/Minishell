/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:12:07 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/23 15:31:00 by loadjou          ###   ########.fr       */
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
	if (!envp)
		return (NULL);
	while (envp && envp[pos + 1])
	{
		envp[pos] = envp[pos + 1];
		pos++;
	}
	envp[pos] = NULL;
	return (envp);
}

char	*cmd_trimmed(char *envp)
{
	char	*cmd;

	cmd = ft_substr(envp, 0, ft_strlen_c(envp, '='));
	if (!cmd || !envp)
		return (NULL);
	return (cmd);
}
