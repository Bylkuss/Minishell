/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:19:35 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/30 14:25:49 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getpath(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_ncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = str_ndup(path, str_ichr(path, ':'));
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = str_split(cmd, ' ');
	if (str_ichr(args[0], '/') > -1)
		path = args[0];
	else
		path = getpath(args[0], env);
	execve(path, args, env);
	write(STDERR, cmd, str_ichr(cmd, 0));
	exit(127);
}

void	redir(char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		dup2(pipefd[0], STDIN);
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		dup2(pipefd[1], STDOUT);
		close(pipefd[0]);
		if (fdin == STDIN)
			exit(1);
		else
			exec(cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	i = 3;
	if (ac >= 5)
	{
		fdin = open(av[1], O_RDONLY);
		if (fdin < 0)
		{
			write(STDERR, av[1], (str_ichr(av[1], 0)));
			write(STDERR, ": No such file\n", 15);
			exit (127);
		}
		fdout = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		redir(av[2], env, fdin);
		while (i < ac - 2)
			redir(av[i++], env, 1);
		exec(av[i], env);
	}
	else
		write(STDERR, "Invalid number of arguments.\n", 30);
	return (1);
}
