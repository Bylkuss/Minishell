#include "pipex.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}

char	*getcmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = path_join(*paths, "/");
		command = path_join(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

// char	*getpath(char *cmd, char **env)
	// {
	// 	char	*path;
	// 	char	*dir;
	// 	char	*bin;
	// 	int		i;

	// 	i = 0;
	// 	while (env[i] && str_ncmp(env[i], "PATH=", 5))
	// 		i++;
	// 	if (!env[i])
	// 		return (cmd);
	// 	path = env[i] + 5;
	// 	while (path && str_ichr(path, ':') > -1)
	// 	{
	// 		dir = str_ndup(path, str_ichr(path, ':'));
	// 		bin = path_join(dir, cmd);
	// 		free(dir);
	// 		if (access(bin, F_OK) == 0)
	// 			return (bin);
	// 		free(bin);
	// 		path += str_ichr(path, ':') + 1;
	// 	}
	// 	return (cmd);
// }




void	first_child(t_pipex pipex, char **av, char **envp) 
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = str_split(av[2], ' ');
	if (str_ichr(pipex.cmd_args[0], '/') > -1)
		pipex.cmd = pipex.cmd_args[0];
	else
		pipex.cmd = getcmd(envp, pipex.cmd_args[0] );

	// pipex.cmd = getcmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
        write(2, ERR_CMD, str_ichr(ERR_CMD, 0));
		// msg(ERR_CMD);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = str_split(av[3], ' ');
	pipex.cmd = getcmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
        write(2, ERR_CMD, str_ichr(ERR_CMD, 0));
		// msg(ERR_CMD);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

// void close_pipe(t_pipex *pipex)
// {
// 	close(pipex->tube[0]);
// 	close(pipex->tube[1]);
// }