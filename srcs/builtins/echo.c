/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:29 by loadjou           #+#    #+#             */
/*   Updated: 2023/03/21 15:22:27 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	multiple_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			break ;
	}
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

static void	print_echo(char **cmd, int flag)
{
	int	i;
	int	j;

	j = 0;
	i = flag + 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "$?"))
		{
			printf("%s", cmd[i]);
			return ;
		}
		j = 0;
		while (cmd[i][j])
		{
			printf("%c", cmd[i][j]);
			j++;
		}
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

int	echo(char **cmd)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	if (!cmd[1])
	{
		printf("\n");
		return (1);
	}
	if (ft_strcmp(cmd[1], "-n") == 0 || multiple_n(cmd[1]) == 1)
		flag = 1;
	if (cmd[1])
		print_echo(cmd, flag);
	if (flag == 0)
	{
		printf("\n");
		return (1);
	}
	return (0);
}
