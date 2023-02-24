/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 03:39:28 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/24 03:39:31 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

extern int g_status;

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
		return (255);
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

void *chk_error(int err_type, char *param, int err)
{
    g_status = err;
    if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected node `|'\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
    return (NULL);
}


void free_cont(void *content)
{
    t_node *node;

    node = content;
    ft_mx_free(&node->cmd);
    free(node->path);
    if (node->infile != STDIN_FILENO)
        close(node->infile);
    if (node->outfile != STDOUT_FILENO)
        close(node->outfile);
    free(node);
}