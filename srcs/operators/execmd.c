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
	printf("DEBUG: TEST find_command \n");//>> cmd{%s}  \n", cmd);
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

static DIR	*cmd_checks(t_table *tab, t_list *cmd, char ***s, char *path)
{
	DIR		*dir;
	t_node	*n;

		printf("DEBUG: START cmd_chk ... \n");
	dir = NULL;
	n = cmd->content;
	if (n && n->cmd)// && ft_strchr(path, '/') && !dir) //*tab instead of tab!?
		dir = opendir(*n->cmd);
	if (n && n->cmd && ft_strchr(*n->cmd, '/') && !dir) //*tab instead of tab!?
	{
		printf("DEBUG: __FIRST_IF cmd_chk ... \n");
		*s = ft_split(*n->cmd, '/');
		n->path = ft_strdup(*n->cmd);
		free(n->cmd[0]);
		n->cmd[0] = ft_strdup(s[0][ft_mx_len(*s) - 1]);
	}
	else if (!is_builtin(n) && n &&n->cmd && !dir)
	{
		printf("DEBUG: __TEST -- ELSE --cmd_chk ... \n");
		path = ms_getenv("PATH", tab->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		n->path = find_command(*s, *n->cmd, n->path);

		if (!n->path || !n->cmd[0] || !n->cmd[0][0])
			chk_error(NCMD, *n->cmd, 127);
	}		
	return (dir);
}


void 	get_cmd(t_table *tab, t_list *cmd, char **s, char *path)
{
	DIR		*dir;
	t_node	*n;

		// printf("DEBUG: START cmd_chk ... \n");
			// printf("DEBUG::__TEST get_cmd ==> {%s}\n", *t->cmd);
			// if (!tab->node->path)
			// 	tab->node->path = getpath(tab->node->cmd[0], tab->envp);
	n = cmd->content;
	dir = cmd_checks(tab, cmd, &s, path);
	if (!is_builtin(n) && n && n->cmd && dir)
		chk_error(IS_DIR, *n->cmd, 126);
	else if (!is_builtin(n) && n && n->path && access(n->path, F_OK) == -1)
		chk_error(NDIR, n->path, 127);
	else if (!is_builtin(n) && n && n->path && access(n->path, X_OK) == -1)
		chk_error(NPERM, n->path, 126);
	if (dir)
		closedir(dir); 
	//ft_mx_free();

	// return (t->path);
			// t->path = ft_strdup((const char*)full_path);
			// printf("DEBUG::: get_cmd t->full {%s} \n", t->full);
			// printf("DEBUG::: get_cmd t->xfile {%s} \n", t->xfile);
		// printf("\nDEBUG::: CHKCHK get_cmd t->lead {%s} \n", t->lead);
		// printf("\nDEBUG::: CHKCHK get_cmd t->path{%s} \n", t->path);
}

void *execmd(t_table *tab, t_list *cmd)
{
    int fd[2];
	char *path;
	
	if (tab->node->path)
		tab->node->path = NULL;
    get_cmd(tab, cmd, NULL, NULL);
	printf("DEBUG:__TEST execmd [id]>> infile[] + outfile[] \n");//, t->id, t->infile, t->outfile);
	// printf("DEBUG: __TEST execmd ::t->cmd{%s}\n", *t->cmd);
	// printf("DEBUG:__TEST execmd >> path{%s} + cmd{%s} \n", tab->node->path, *tab->node->cmd);
    if (pipe(fd) == -1)
        return (chk_error(PIPERR, NULL, 1));
    if (!chk_fork(tab, cmd, fd))
        return (NULL);
	printf("read_end = %d write_end = %d\n", READ_END, WRITE_END);
	if (tab->cmdl->next && !((t_node *)tab->cmdl->next->content)->infile)// ouf?  next t->infile
		((t_node *)tab->cmdl->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
    close(fd[WRITE_END]);
	// printf("DEBUG: __INTO__ execmd >> infile[%d] + outfile[%d] \n\n", n->infile, n->outfile);
	if (((t_node *)tab->cmdl->content)->infile > 2)
		close(((t_node *)tab->cmdl->content)->infile);
	if (((t_node *)tab->cmdl->content)->outfile > 2)
		close(((t_node *)tab->cmdl->content)->outfile);
	return (NULL);

}