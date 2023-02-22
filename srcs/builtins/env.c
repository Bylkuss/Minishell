/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:12:07 by bylkus            #+#    #+#             */
/*   Updated: 2023/01/23 10:37:21 by loadjou          ###   ########.fr       */
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
	// printf("**********END***********\n");
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

int	ft_strcmp_c(char *s1, char *s2, char until)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != until)
		i++;
	return (s1[i] - s2[i]);
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
		if (ft_strncmp(envp[i], var, ft_strlen_c(envp[i], '=')) == 0)
			return (i);
		// if (ft_strcmp_c(envp[i], var, '=') == 0)
		i++;
	}
	return (-1);
}

char	**new_envp(char **envp, char *var)
{
	int		i;
	int		pos;
	int		len;
	char	**new_envp;

	len = ft_arraylen(envp) + 2;
	new_envp = ft_calloc(sizeof(char *), len);
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		// printf("%s\n", new_envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(var);
	// ft_free_array(envp);
	return (new_envp);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	ms_export(char **cmd, char **envp)
{
	int	pos;

	// printf("%s\n", cmd[1]);
	if (cmd[1] && check_export_cmd(cmd[1]))
	{
		pos = is_already_var(envp, cmd[1]);
		// printf("pos [%d]\n", is_already_var(envp, cmd[1]));
		if (pos > -1)
			envp[pos] = ft_strdup(cmd[1]);
		else
		{
			
			envp = new_envp(envp, cmd[1]);
			// print_tab(envp);
		}
		// printf("%s is a valid var\n\n\n", cmd[1]);
		// print_tab(envp);
		if (!envp)
			return (0);
	}
	else if (!cmd[1])
		env(envp);
	else
	{
		printf("Bad var format\n");
		return (0);
	}
	return (1);
}
