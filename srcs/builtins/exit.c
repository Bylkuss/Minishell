/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:26:43 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/14 20:35:27 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_builtin(char **cmd)
{
	int	exiit;
	int	i;

	exiit = 0;
	i = 0;
	if (cmd[1] && !cmd[2])
	{
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
			{
				printf("exit: numeric argument required\n");
				exit(2);
			}
			i++;
		}
		exiit = ft_atoi(cmd[1]);
	}
	exit(exiit);
	return (exiit);
}
