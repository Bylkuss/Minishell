/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:47:23 by loadjou           #+#    #+#             */
/*   Updated: 2023/03/23 15:48:04 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	unset(char **cmd, char **envp)
{
	int		i;
	int		j;
	char	*cmd_trim;

	j = 1;
	g_status = 1;
	while (cmd[j])
	{
		printf("Missmatch args nb\n");
		return (0);
	}
	while (envp[i])
	{
		cmd_trim = cmd_trimmed(envp[i]);
		if (ft_strcmp(cmd_trim, cmd[1]) == 0)
		{
			envp = edit_env(envp, i);
			free(cmd_trim);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	var_envp(char *argv, char **envp, int k[2])
{
	int	pos;

	k[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[k[1]])
	{
		if (!ft_strncmp(envp[k[1]], argv, pos + 1))
			return (1);
		k[1]++;
	}
	return (0);
}

int	ms_unset(t_table *tab)
{
	char	**argv;
	char	*aux;
	int		k[2];

	k[0] = 0;
	argv = ((t_node *)tab->cmdl->content)->cmd;
	if (ft_mx_len(argv) >= 2)
	{
		while (argv[++k[0]])
		{
			if (argv[k[0]][ft_strlen(argv[k[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[k[0]], "=");
				free(argv[k[0]]);
				argv[k[0]] = aux;
			}
			if (var_envp(argv[k[0]], tab->envp, k))
				ft_mx_rpl(&tab->envp, NULL, k[1]);
		}
	}
	return (0);
}
