/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:33:02 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/16 00:42:22 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
extern int g_status;


static char	*find_command(char **env_path, char *cmd, char *path)
{
	char	*temp;
	int		i;

	i = -1;
	// printf("DEBUG: TEST find_command >> path{%s}  \n", path);
	// printf("DEBUG: TEST find_command >> cmd{%s}  \n", cmd);
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

static DIR	*cmd_checks(t_table *tab, t_node *t, char **s, char *path)
{
	DIR		*dir;

		// printf("DEBUG: START cmd_chk ... \n");
	dir = opendir(path);
	if (t && path && ft_strchr(path, '/') && !dir) //*tab instead of tab!?
	{
		// printf("DEBUG: __FIRST_IF cmd_chk ... \n");
		s = ft_split(path, '/');
		path = ft_strdup((const char *)s);
		// free(path);
		path = ft_strdup(s[ft_mx_len(s) - 1]);
	}
	else if (!is_builtin(t) && t && path && !dir)
	{
		// printf("DEBUG: __TEST -- ELSE --cmd_chk ... \n");
		path = ms_getenv("PATH", tab->envp, 4);
		s = ft_split(path, ':');
		free(t->path);
		t->path = find_command(s, *t->cmd, path);

		if (!t->path || !(*t->cmd))// || !t->cmd[0][0])
			chk_error(NCMD, *t->cmd, 127);
	}		
	return (dir);
}

char	*getpath(char *cmd, char **env)
{
	char	*dir;
	char	*bin;
	int		i;
	char 	*path;

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
		// printf("DEBUG: INTO__getpath bin{%s}\n\n", bin);//cmd);
	return (cmd);
}

void 	get_cmd(t_table *tab, t_node *t)
{
	DIR		*dir;

	// printf("DEBUG::__TEST get_cmd ==> {%s}\n", *t->cmd);
	if (!t->path)
		t->path = getpath(*t->cmd, tab->envp);
	dir = cmd_checks(tab, t, tab->envp, t->path);
	if (!is_builtin(t) && t && *t->cmd && dir)
		chk_error(IS_DIR, t->path, 126);
	else if (!is_builtin(t) && t && t->path && access(t->path, F_OK) == -1)
		chk_error(NDIR, t->path, 127);
	else if (!is_builtin(t) && t && t->path && access(t->path, X_OK) == -1)
		chk_error(NPERM, t->path, 126);
	if (dir)
		closedir(dir); 
	// return (t->path);
			// t->path = ft_strdup((const char*)full_path);
			// printf("DEBUG::: get_cmd t->full {%s} \n", t->full);
			// printf("DEBUG::: get_cmd t->xfile {%s} \n", t->xfile);
		// printf("\nDEBUG::: CHKCHK get_cmd t->lead {%s} \n", t->lead);
		// printf("\nDEBUG::: CHKCHK get_cmd t->path{%s} \n", t->path);
}

void *execmd(t_table *tab, t_node *t)
{
    int fd[2];
	char *path;
	
	if (t->path)
		t->path = NULL;
	printf("DEBUG:__TEST execmd [id%d]>> infile[%d] + outfile[%d] \n", t->id, t->infile, t->outfile);
    get_cmd(tab, t);
	// printf("DEBUG: __TEST execmd ::t->cmd{%s}\n", *t->cmd);
	printf("DEBUG: __TEST execmd >> path{%s} + cmd{%s} \n", t->path, *t->cmd);
    if (pipe(fd) == -1)
        return (chk_error(PIPERR, NULL, 1));
    if (!chk_fork(tab, t, fd))
        return (NULL);
	printf("read_end = %d write_end = %d\n", READ_END, WRITE_END);
	if (t->etype == 1 )//&& !(t->infile))// ouf?  next t->infile
		t->outfile = fd[WRITE_END];//??
	else
		close(fd[READ_END]);
    close(fd[WRITE_END]);
	printf("DEBUG: __INTO__ execmd >> infile[%d] + outfile[%d] \n\n", t->infile, t->outfile);
	if (t->infile > 2)
		close(t->infile);
	if (t->outfile > 2)
		close(t->outfile);
	return (NULL);

}