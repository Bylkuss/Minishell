/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:29:09 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/23 14:02:20 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(char **cmd, char **envp)
{
	int		i;
	char	*cmd_trim;

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
			envp = edit_env(envp, i);
			free(cmd_trim);
			return (1);
		}
		i++;
	}
	return (0);
}
