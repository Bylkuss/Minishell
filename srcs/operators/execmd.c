#include "../../includes/minishell.h"
extern int g_status;


static char	*find_command(char **env_path, char *cmd, char *path)
{
	char	*temp;
	int		i;

	i = -1;
	path = NULL;
	while (env_path && env_path[++i])
	{
		free(path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static DIR	*cmd_checks(t_table *tab, t_token *token, char **s, char *path)
{
	t_token	*t;
	DIR		*dir;

	dir = NULL;
	t = token;
	if (t && t->cmd)
		dir = opendir(*t->cmd);
	if (t && t->cmd && ft_strchr(*t->cmd, '/') && !dir) //*tab instead of tab!?
	{
		*s = ft_split(*t->cmd, '/');
		t->path = ft_strdup(*t->cmd);
		free(t->cmd);
		t->cmd[0] = ft_strdup(s[0][ft_mx_len(*s) - 1]);
	}
	else if (!is_builtin(t) && t && t->cmd && !dir)
	{
		path = ms_getenv("PATH", tab->envp, 4);
		s = ft_split(path, ':');
		free(path);
		t->path = find_command(s, *t->cmd, t->path);

		if (!t->path || !t->cmd[0])// || !t->cmd[0][0])
			chk_error(NCMD, *t->cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_table *tab, t_token *token)
{
	t_token	*t;
	DIR		*dir;

	t = token;
	dir = cmd_checks(tab, t, tab->envp, t->path);
	if (!is_builtin(t) && t && t->cmd && dir)
		chk_error(IS_DIR, *t->cmd, 126);
	else if (!is_builtin(t) && t && t->path && access(t->path, F_OK) == -1)
		chk_error(NDIR, t->path, 127);
	else if (!is_builtin(t) && t && t->path && access(t->path, X_OK) == -1)
		chk_error(NPERM, t->path, 126);
	if (dir)
		closedir(dir); 
}

void *execmd(t_table *tab, t_token *token, int id)
{
    int fd[2];
    t_token *t;

    get_cmd(tab, t);
    if (pipe(fd) == -1)
        return (chk_error(PIPERR, NULL, 1));
    if (!chk_fork(tab, t, id, fd))
        return (NULL);
    close(fd[WRITE_END]);
	if (t->endtype > 3 && !(t->infile))// ouf?  next t->infile
		t->infile = fd[READ_END];//??
	else
		close(fd[READ_END]);
	if (t->infile > 2)
		close(t->infile);
	if (t->outfile > 2)
		close(t->outfile);
	return (NULL);

}