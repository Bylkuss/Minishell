/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:32:42 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/22 21:43:04 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
extern int g_status;

void	child_builtin(t_table *tab, t_token *t, int id)
{
    int l;  //cmd len

    l = ft_strlen(t->cmd[0]);	
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(t) && t->cmd)
		execve(t->path, t->cmd, tab->envp);
	// else if (t->cmd && !ft_strncmp(*t->cmd, "pwd", l) && l == 3)
	// 	g_status = pwd();
	// else if (is_builtin(t) && t->cmd && !ft_strncmp(*t->cmd, "echo", l) && l == 4)
	// // 	g_status = echo(cmd);
	// else if (is_builtin(t) && t->cmd && !ft_strncmp(*t->cmd, "env", l) && l == 3)
	// {
	// 	// ft_putmatrix_fd(tab->envp, 1, 1);
	// 	g_status = 0;
	// }
}

static void	*child_redir(t_token *t, int id, int fd[2])
{
    // t_token	*t;

	// t = token;
		// printf("DEBUG: TEST child_redir \n");
	if (t->infile != STDIN_FILENO)
	{
		if (dup2(t->infile, STDIN_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(t->infile);
	}
	if (t->outfile != STDOUT_FILENO)
	{
		if (dup2(t->outfile, STDOUT_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(t->outfile);
	}
	else if (t->endtype && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (chk_error(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*born_child(t_table *tab, t_token *t, int id, int fd[2])
{
    // t_token*t;
	int		l;

	// t = token;
	l = 0;
	if (t->cmd)
		l = ft_strlen(t->cmd[0]);

	child_redir(t, id, fd);

	close(fd[READ_END]);

	child_builtin(tab, t, id);
    // remove token
    // free_cont
	// ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void    exc_fork(t_table *tab, t_token *t, int id, int fd[2])
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
		born_child(tab, t, id, fd);
}

void *chk_fork(t_table *tab, t_token *t, int id, int fd[2])
{
    // t_token *t;
    DIR     *dir;
	printf("DEBUG: TEST chk_fork \n");
    // t = token;
    dir = NULL;
    if (t->cmd)
        dir = opendir(t->path);
    if (t->infile == -1 || t->outfile == -1)
        return (NULL);
    if ((t->path && access(t->path, X_OK) == 0) || is_builtin(t))
        exc_fork(tab, t, id, fd);
    else if (!is_builtin(t) && ((t->path && !access(t->path, F_OK)) || dir))
	{
		printf("DEBUG: GRR.. exc_frk\n");
        g_status = 126;
	}
    else if (!is_builtin(t) && t->full)
        g_status = 127;
    if (dir)
        closedir(dir);
    return ("");
}