/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:32:42 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/22 14:02:14 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	child_builtin(t_table *tab, t_node *n, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(n) && n->cmd)
		execve(n->path, n->cmd, tab->envp);
	else if (n->cmd && !ft_strncmp(*n->cmd, "pwd", l) && l == 3)
		g_status = pwd();
	else if (is_builtin(n) && n->cmd && !ft_strncmp(*n->cmd, "echo", l)
		&& l == 4)
		g_status = echo(n->cmd);
	else if (is_builtin(n) && cmd && !ft_strncmp(*n->cmd, "env", l) && l == 3)
	{
		ft_mx_fd(tab->envp, 1);
		g_status = 0;
	}
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_node	*n;

	n = cmd->content;
	if (n->infile != STDIN_FILENO)
	{
		if (dup2(n->infile, STDIN_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(n->infile);
	}
	if (n->outfile != STDOUT_FILENO)
	{
		if (dup2(n->outfile, STDOUT_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(n->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (chk_error(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*born_child(t_table *tab, t_list *cmd, int fd[2])
{
	t_node	*n;
	int		l;

	l = 0;
	n = cmd->content;
	if (n->cmd)
		l = ft_strlen(*n->cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
	child_builtin(tab, n, l, cmd);
	ft_lstclear(&tab->cmdl, free_cont);
	exit(g_status);
}

void	exc_fork(t_table *tab, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		chk_error(FORKERR, NULL, 1);
	}
	else if (!pid)
		born_child(tab, cmd, fd);
}

void	*chk_fork(t_table *tab, t_list *cmd, int fd[2])
{
	DIR		*dir;
	t_node	*n;

	n = cmd->content;
	dir = NULL;
	if (n->cmd)
		dir = opendir(*n->cmd);
	if (n->infile == -1 || n->outfile == -1)
		return (NULL);
	if ((n->path && access(n->path, X_OK) == 0) || is_builtin(n))
		exc_fork(tab, cmd, fd);
	else if (!is_builtin(n) && ((n->path && !access(n->path, F_OK)) || dir))
		g_status = 126;
	else if (!is_builtin(n) && n->cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
