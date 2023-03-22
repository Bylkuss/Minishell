/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:26:43 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/21 15:22:44 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (status[0]);
}
