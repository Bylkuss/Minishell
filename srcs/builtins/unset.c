/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:29:09 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/23 14:16:54 by loadjou          ###   ########.fr       */
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
		i = 0;
		while (envp[i])
		{
			cmd_trim = cmd_trimmed(envp[i]);
			if (ft_strcmp(cmd_trim, cmd[j]) == 0)
			{
				envp = edit_env(envp, i);
				free(envp[i]);
				g_status = 0;
			}
			free(cmd_trim);
			i++;
		}
		j++;
	}
	if (!cmd[1])
		ft_putstr_fd("Missmatch args nb\n", 2);
	return (g_status);
}
