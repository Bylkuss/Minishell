/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:26:43 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/20 10:08:19 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	exit_builtin(char **cmd)
// {
// 	int	exiit;
// 	int	i;

// 	exiit = 0;
// 	i = 0;
// 	if (cmd[1] && !cmd[2])
// 	{
// 		while (cmd[1][i])
// 		{
// 			if (!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
// 			{
// 				printf("exit: numeric argument required\n");
// 				return(2);//exit(2);
// 			}
// 			i++;
// 		}
// 		exiit = ft_atoi(cmd[1]);
// 	}
// 	// exit(exiit);
// 	printf("builins_status=[%d]\n", exiit);
// 	return (exiit);
// }

int	ms_exit(t_list *cmdl, int *is_exit)
{
	t_node	*node;
	long	status[2];

	node = cmdl->content;
	*is_exit = !cmdl->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node->cmd || !node->cmd[1])
		return (0);
	status[1] = ft_atoi2(node->cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	else if (node->cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	printf("status=[%ld]\n", status[0]);
	return (status[0]);
}
