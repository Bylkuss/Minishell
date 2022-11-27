/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:29 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/27 13:41:16 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*Thereis_n() funtion checks if we received the "-n" option with echo
with all his possibilities. meaning: with all quotes posibilities */
int	thereis_n(char **cmd)
{
	char opt[] = "-n";
	int flag = 0;
	int i = 0;
	int j = 0;
	int s_qt = 0;
	int d_qt = 0;
	while(cmd[1][i])
	{
		if(cmd[1][i] == '\'')
			s_qt++;
		else if(cmd[1][i] == '"')
			d_qt++;
		i++;
	}
	if(d_qt % 2 == 0 || s_qt % 2 == 0)
		flag = 1;
	i = 0;
	while(cmd[1][i] && opt[j])
	{
		if(flag == 1 && cmd[1][i] == '\'' || cmd[1][i] == '"')
			i++;
		else if(cmd[1][i] != opt[j])
			break;
		i++;
		j++;
	}
	return 0;
}

int	check_quote(char **cmd)
{
	int i = 0;
	int s_qt = 0;
	int d_qt = 0;
	while(cmd[1][i])
	{
		if(cmd[1][i] == '\'')
			s_qt++;
		else if(cmd[1][i] == '"')
			d_qt++;
		i++;
	}
	if(d_qt % 2 != 0 || s_qt % 2 != 0)
		return(0);
	return 1;
}
/*echo() function receives the command as **cmd and execute it.
	input ex: echo -n "Hello world" */
void	echo(char **cmd)
{
	int i;
	int j = 1;
	if(thereis_n(cmd))
		j = 2;
	while(cmd[j])
	{
		i = 0;
		// printf("%d ", j);
		while (cmd[j][i])
		{
			write(1, &cmd[j][i], 1);
			i++;
		}
		write(1, " ", 1);
		j++;
	}
	if(!thereis_n(cmd))
		write(1, "\n", 1);
}