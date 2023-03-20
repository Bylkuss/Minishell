/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:31:44 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/20 12:29:43 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

static int	check_export_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] != '=')
		{
			if (!ft_isalpha(str[i]) && str[i] != '_')
				return (0);
			i++;
		}
		if (i > 0 && str[i] == '=' && str[i + 1] != '=' && str[i - 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

static int	is_already_var(char **envp, char *var)
{
	int		i;
	char	*cmd_trim;
	char	*envp_trim;

	i = 0;
	while (envp[i])
	{
		cmd_trim = cmd_trimmed(var);
		envp_trim = cmd_trimmed(envp[i]);
		if (ft_strcmp(envp_trim, cmd_trim) == 0)
		{
			free(cmd_trim);
			free(envp_trim);
			return (i);
		}
		free(cmd_trim);
		free(envp_trim);
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
		i++;
	}
	new_envp[i] = ft_strdup(var);
	ft_mx_free(&envp);
	return (new_envp);
}

char	**ms_export(char **cmd, char **envp)
{
	int	pos;

	if(!check_export_cmd(cmd[1]))
		g_status = 1;
	if (cmd[1])
	{
		pos = is_already_var(envp, cmd[1]);
		if (pos > -1)
			envp[pos] = ft_strdup(cmd[1]);
		else
			envp = new_envp(envp, cmd[1]);
	}
	else if (!cmd[1])
		print_tab(envp);
	else
		g_status = 0;	
	return (envp);
}
