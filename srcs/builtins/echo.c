/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:29 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/29 10:27:16 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(char **cmd, int flag)
{
	int	i;

	int j= 0;
	i = flag + 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			printf("%c", cmd[i][j]);
			j++;
		}
		printf(" ");
		i++;
	}
}

void	echo(char **cmd)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(cmd[1], "-n") == 0)
		flag = 1;
	if (cmd[1])
	{
		print_echo(cmd, flag);
	}
	if (flag == 0)
		printf("\n");
}
