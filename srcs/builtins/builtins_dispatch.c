/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:54:28 by bylkus            #+#    #+#             */
/*   Updated: 2023/04/03 10:59:51 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static int	is_builtin_1(t_node *t, int l)
{
	if (!ft_strncmp(*t->cmd, "pwd", l) && l == 3)
		return (1);
	if ((!ft_strncmp(*t->cmd, "env", l) || !ft_strncmp(*t->cmd, "ENV", l))
		&& l == 3)
		return (1);
	if (!ft_strncmp(*t->cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*t->cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*t->cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*t->cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*t->cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}

int	is_builtin(t_node *t)
{
	int	l;
	int	id;

	id = 0;
	if (!(t->cmd[0]))
		return (0);
	if (t->cmd && ft_strchr(*t->cmd, '/') || (t->path && ft_strchr(t->path,
				'/')))
		return (0);
	l = ft_strlen(*t->cmd);
	if (is_builtin_1(t, l))
		return (1);
	return (0);
}

int	builtins(t_table *tab, t_list *cmdl, int *is_exit)
{
	char	**aux;
	int		i;

	g_status = 0;
	while (cmdl)
	{
		aux = ((t_node *)cmdl->content)->cmd;
		i = 0;
		if (aux)
			i = ft_strlen(*aux);
		if (aux && !ft_strncmp(*aux, "exit", i) && i == 4)
			g_status = ms_exit(cmdl, is_exit);
		else if (!cmdl->next && aux && !ft_strncmp(*aux, "cd", i) && i == 2)
			g_status = cd(aux, tab->envp);
		else if (!cmdl->next && aux && !ft_strncmp(*aux, "export", i) && i == 6)
			tab->envp = ms_export(aux, tab->envp);
		else if (!cmdl->next && aux && !ft_strncmp(*aux, "unset", i) && i == 5)
			g_status = ms_unset(tab);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			execmd(tab, cmdl);
		}
		cmdl = cmdl->next;
	}
	return (g_status);
}
