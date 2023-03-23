/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:31:44 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/23 12:03:26 by loadjou          ###   ########.fr       */
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
		else
			return (0);
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
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_export_cmd(cmd[i]))
		{
			pos = is_already_var(envp, cmd[i]);
			if (pos > -1)
				envp[pos] = ft_strdup(cmd[i]);
			else
				envp = new_envp(envp, cmd[i]);
		}
		else if (i > 1 && !check_export_cmd(cmd[i]))
		{
			g_status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", cmd[2]);
		}
		i++;
	}
	if (!cmd[1])
		print_tab(envp);
	return (envp);
}
