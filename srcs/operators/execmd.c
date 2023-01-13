#include "../../includes/minishell.h"
extern int g_status;


static char	*find_command(char **env_path, char *cmd, char *path)
{
	char	*temp;
	int		i;

	i = -1;
		// printf("DEBUG: TEST find_command >> path{%s}  \n", path);
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

static DIR	*cmd_checks(t_table *tab, t_token *t, char **s, char *path)
{
	DIR		*dir;

	dir = NULL;
	// printf("DEBUG: START cmd_chk ... \n");
	dir = opendir(path);
	if (t && path && ft_strchr(path, '/') && !dir) //*tab instead of tab!?
	{
		printf("DEBUG: FIRST_IF cmd_chk ... \n");
		s = ft_split(path, '/');
		path = ft_strdup((const char *)s);
		// free(path);
		path = ft_strdup(s[ft_mx_len(s) - 1]);
	}
	else if (!is_builtin(t) && t && path && !dir)
	{
		printf("DEBUG: TEST -- ELSE --cmd_chk ... \n");
		path = ms_getenv("PATH", tab->envp, 4);
		s = ft_split(path, ':');
		free(t->path);
		t->path = find_command(s, *t->cmd[0], path);

		if (!t->path || !t->cmd[0])// || !t->cmd[0][0])
			chk_error(NCMD, *t->cmd[0], 127);
	}		
	return (dir);
}

char	*getpath(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	// printf("DEBUG: TEST getpath ");
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

void 	get_cmd(t_table *tab, t_token *t)
{
	char	*full_path;
	DIR		*dir;

	// t = token;
	// printf("DEBUG::: get_cmd ==> {%s}\n", t->cmd[0]);
	full_path = getpath(*t->cmd[0], tab->envp);
	t->path = ft_strdup((const char*)full_path);
	// printf("DEBUG::: cmd_path {%s} \n", t->path);
	dir = cmd_checks(tab, t, tab->envp, full_path);
	if (!is_builtin(t) && t && t->cmd && dir)
		chk_error(IS_DIR, *t->cmd, 126);
	else if (!is_builtin(t) && t && t->path && access(t->path, F_OK) == -1)
		chk_error(NDIR, t->path, 127);
	else if (!is_builtin(t) && t && t->path && access(t->path, X_OK) == -1)
		chk_error(NPERM, t->path, 126);
	if (dir)
		closedir(dir); 
	// return (t->path);
}

void *execmd(t_table *tab, t_token *t, int id)
{
    int fd[2];
	char *path;

	// printf("DEBUG: TEST execmd  ");
    get_cmd(tab, t);
	if (t->path)
		printf("DEBUG: TEST execmd >> path{%s} + cmd{%s} \n", t->path, *t->cmd[0]);
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