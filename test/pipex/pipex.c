/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:19:05 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/06 11:04:02 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>


void close_pipe(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	msg(char *err)
{
	write(2, err, str_ichr(err, 0));
	return (1);
}

void	msg_error(char *err)
{
	perror(err);
	exit (1);
}

char	*getpath(char **env)
{
	while (*env && str_ncmp(*env, "PATH=", 5))
		env++;
	return (*env + 5);
}
// char	*getcmd(char **paths, char *cmd)
	// {
	// 	char	*tmp;
	// 	char	*command;

	// 	while (*paths)
	// 	{
	// 		tmp = path_join(*paths, "/");
	// 		command = path_join(tmp, cmd);
	// 		free(tmp);
	// 		if (access(command, 0) == 0)
	// 			return (command);
	// 		free(command);
	// 		paths++;
	// 	}
	// 	return (NULL);
// }

void	redir(t_pipex pipex, char **av, char **envp)
{
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);

	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, envp);	
	// close_pipe(&pipex);
	// waitpid(pipex.pid1, NULL, 0);
	// waitpid(pipex.pid2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;

	if (ac == 5)
	{
		pipex.infile = open(av[1], O_RDONLY);
		if (pipex.infile < 0)
			msg_error(ERR_INFILE);

		pipex.outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		pipe(pipex.tube);
		if (pipe(pipex.tube) < 0)
			msg_error(ERR_PIPE);
		pipex.paths =  getpath(envp);
		pipex.cmd_paths = str_split(pipex.paths, ':');
		redir(pipex, av, envp);
		close_pipe(&pipex);
		waitpid(pipex.pid1, NULL, 0);	
		waitpid(pipex.pid2, NULL, 0);
		close(pipex.infile);
		close(pipex.outfile);
		parent_free(&pipex);
	}
	else
		return (msg(ERR_INPUT));		// write(STDERR, "Wrong number of arguments\n", 26);
	return (1);
}
