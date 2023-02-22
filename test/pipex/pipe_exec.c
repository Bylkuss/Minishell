/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:40:47 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/31 13:10:30 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "pipex.h"

int	execute_cmd(t_table *tab, t_token *tok)
{
	int pipe_fd[2];
	pipe(pipe_fd);
	char *path_cmd;

	path_cmd = getpath(tok->cmd[0], tab->envp);
	int pid = fork();
	if (pid == 0 && path_cmd)
	{
		// child process
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execve(path_cmd, tok->cmd, tab->envp);
		return (pipe_fd[1]);
	}
	else
	{
		// parent process
		close(pipe_fd[1]);
		tok->infile = open(tok->ofile, O_RDONLY);
		dup2(tok->infile, STDIN_FILENO);
		tok->outfile = open("outfile.txt", O_WRONLY | O_CREAT, 0664);
		dup2(tok->outfile, STDOUT_FILENO);
		dup2(pipe_fd[0], STDOUT_FILENO);
		waitpid(tok->outfile);
	}
	return (-1);
}