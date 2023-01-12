#include "../../includes/minishell.h"
extern int g_status;


static char	*find_command(char **env_path, char *cmd, char *path)
{
	char	*temp;
	int		i;

	i = -1;
	path = NULL;
	printf("DEBUG: into F_com ...{%s} \n", path);
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
		printf("DEBUG: while F_com ...{%s} \n", path);
		if (access(path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(path);
		return (NULL);
	}
	printf("DEBUG: into F_com ...{%s} \n", path);
	return (path);
}

static char	*cmd_checks(t_table *tab, t_token *token, char **s, char *path)
{
	t_token	*t;
	DIR		*dir;

	dir = NULL;
	t = token;

	printf("DEBUG: cmd_chk {%s}path \n", t->cmd[0]);
	if (t && t->cmd && !t->path)
		dir = opendir(t->path);

	path = find_command(tab->envp, t->cmd[0], t->path);
	if (path)
		printf("DEBUG: cmd_chk t->path {%s} \n", path);
	else if (tab->token->path)
		printf("DEBUG: cmd_chk tab->path \n");//== {%s} \n", tab->token->path);
	else if (!t->path && !tab->token->path)
		printf("DEBUG: cmd_chk NO path \n");

	if (t && t->cmd && ft_strchr(t->path, '/') && !dir) //*tab instead of tab!?
	{
		printf("DEBUG: cmd_chk path == / \n");
		// *s = ft_split(t->path, '/');
		// t->path = ft_strdup(t->cmd);
		// free(t->cmd);
		// t->cmd[0] = ft_strdup(s[0][ft_mx_len(*s) - 1]);
	}
	else if (!is_builtin(t) && t && t->cmd)// && t->path)
	{
		printf("DEBUG: cmd_chk !is_builtns \n");
		t->path = ms_getenv("PATH", tab->envp, 4);
		// s = ft_split(path, ':');
		free(path);
		t->path = find_command(tab->envp, t->cmd[0], t->path);

		if (!t->path || !t->cmd[0])// || !t->cmd[0][0])
			chk_error(NCMD, *t->cmd, 127);
	}
	return (t->path);
}

char	*getpath(char **env)
{
	while (*env && str_ncmp(*env, "PATH=", 5))
		env++;
	// printf("DEBUG: into getpath ...{%s} \n", *env);
	return (*env + 5);
}

char	*getcmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	// printf("DEBUG: int getcmd ... \n");
	while (*paths)
	{
		tmp = path_join(*paths, "/");
		command = path_join(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
		{
			printf("DEBUG: into getcmd command = {%s}... \n",command);
			return (command);
		}
		free(command);
		paths++;
	}
	return (NULL);
}

// void	get_cmd(t_table *tab, t_token *token)
	// {
	// 	t_token	*t;
	// 	DIR		*dir;

	// 	t = token;
	// 	t->path = cmd_checks(tab, t, tab->envp, t->path);
	// 	printf("DEBUG: TEST get_cmd \n");
	// 	if (t->path)
	// 		printf("DEBUG: TEST get_cmd IS_PATH{%s} \n", t->path);
	// 	if (!is_builtin(t) && t && t->cmd && t->path)
	// 		chk_error(IS_DIR, *t->cmd, 126);
	// 	else if (!is_builtin(t) && t && t->path && access(t->path, F_OK) == -1)
	// 		chk_error(NDIR, t->path, 127);
	// 	else if (!is_builtin(t) && t && t->path && access(t->path, X_OK) == -1)
	// 		chk_error(NPERM, t->path, 126);
	// 	if (dir)
	// 		closedir(dir); 
// }

void *execmd(t_table *tab, t_token *token, int id)
{
    int fd[2];
    t_token *t;
	char *path;

	printf("DEBUG: TEST execmd\n");
	path = getcmd(tab->envp, token->cmd[0]);
    // get_cmd(tab, t);
	// printf("DEBUG: TEST execmd 2 \n");
	printf("DEBUG: TEST execmd >> path{%s} + cmd{%s} \n", path, token->cmd[0]);
	path = getpath(tab->envp);
	printf("DEBUG: TEST find_command >> path{%s}  \n", path);
	// path = find_command(tab->envp, t->cmd[0], path);
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