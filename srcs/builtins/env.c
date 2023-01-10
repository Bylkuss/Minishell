/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:12:07 by bylkus            #+#    #+#             */
/*   Updated: 2023/01/10 17:31:01 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	// if (!envp[pos + 1])
	// {
	// 	free(envp[pos]);
	// 	envp[pos] = NULL;
	// }
	while (envp && envp[pos + 1])
	{
		// printf("%s\n", envp[pos]);
		envp[pos] = envp[pos + 1];
		pos++;
	}
	// free(envp[pos]);
	envp[pos] = NULL;
	return (envp);
}

int	unset(char **cmd, char **envp)
{
	int	i;

	i = 0;
	if (!cmd[1] || cmd[2])
	{
		printf("Missmatch args nb\n");
		return (0);
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], cmd[1], ft_strlen_c(envp[i], '=')) == 0)
		{
			envp = edit_env(envp, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int ft_strcmp_c(char *s1, char *s2, char until)
{
    int i = 0;
    while(s1[i] && s2[i] && s1[i] != until)
        i++;
    return s1[i] - s2[i];
}

static int	check_export_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == '=' && str[i + 1] != '=' && str[i - 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_already_var(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if(ft_strncmp(envp[i], var, ft_strlen_c(envp[i], '=')) == 0)
			return (i);
		// if (ft_strcmp_c(envp[i], var, '=') == 0)
		i++;
	}
	return (0);
}

int	export(char **cmd, char **envp)
{
	int pos = 0;
	// printf("%s\n", cmd[1]);
	printf("pos [%d]\n", is_already_var(envp, cmd[1]));
	if (cmd[1] && check_export_cmd(cmd[1]))
	{
		printf("%s is a valid var\n", cmd[1]);
		pos = is_already_var(envp, cmd[1]);
		if (pos)
		{
			envp[pos] = NULL;
			envp[pos] = ft_strdup(cmd[1]);
			printf("%s\n", envp[pos]);
		}
		else
		{
			envp[ft_arraylen(envp)] = ft_calloc(sizeof(char *), 1);
			if (!envp[ft_arraylen(envp)])
				return (0);
			envp[ft_arraylen(envp)] = ft_strdup(cmd[1]);
		}
		return (1);
	}
	else
	{
		printf("Bad var format\n");
	}
	return (0);
}
