/*  Test4 follow others... token's end. */

#include "../inc/minishell.h"
extern int	g_status;
- - - - - - 
// redir

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		mini_perror(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		mini_perror(NPERM, path, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mini_perror(NPERM, path, 126);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_mini	*get_outfile1(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_outfile2(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_infile1(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->infile = get_fd(node->infile, args[*i], flags);
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_infile2(t_mini *node, char **args, int *i)
{
	char	*aux[2];
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		node->infile = get_here_doc(str, aux);
	}
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
	}
	return (node);
}


- - - - - -
// cmd_match

static char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static DIR	*cmd_checks(t_prompt *prompt, t_list *cmd, char ***s, char *path)
{
	t_mini	*n;
	DIR		*dir;

	dir = NULL;
	n = cmd->content;
	if (n && n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n && n->full_cmd && ft_strchr(*n->full_cmd, '/') && !dir)
	{
		*s = ft_split(*n->full_cmd, '/');
		n->full_path = ft_strdup(*n->full_cmd);
		free(n->full_cmd[0]);
		n->full_cmd[0] = ft_strdup(s[0][ft_matrixlen(*s) - 1]);
	}
	else if (!is_builtin(n) && n && n->full_cmd && !dir)
	{
		path = mini_getenv("PATH", prompt->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		n->full_path = find_command(*s, *n->full_cmd, n->full_path);
		if (!n->full_path || !n->full_cmd[0] || !n->full_cmd[0][0])
			mini_perror(NCMD, *n->full_cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path)
{
	t_mini	*n;
	DIR		*dir;

	n = cmd->content;
	dir = cmd_checks(prompt, cmd, &s, path);
	if (!is_builtin(n) && n && n->full_cmd && dir)
		mini_perror(IS_DIR, *n->full_cmd, 126);
	else if (!is_builtin(n) && n && n->full_path && \
		access(n->full_path, F_OK) == -1)
		mini_perror(NDIR, n->full_path, 127);
	else if (!is_builtin(n) && n && n->full_path && \
		access(n->full_path, X_OK) == -1)
		mini_perror(NPERM, n->full_path, 126);
	if (dir)
		closedir(dir);
	ft_free_matrix(&s);
}

void	*exec_cmd(t_prompt *prompt, t_list *cmd)
{
	int		fd[2];

	get_cmd(prompt, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (mini_perror(PIPERR, NULL, 1));
	if (!check_to_fork(prompt, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_mini *)cmd->next->content)->infile)
		((t_mini *)cmd->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_mini *)cmd->content)->infile > 2)
		close(((t_mini *)cmd->content)->infile);
	if (((t_mini *)cmd->content)->outfile > 2)
		close(((t_mini *)cmd->content)->outfile);
	return (NULL);
}