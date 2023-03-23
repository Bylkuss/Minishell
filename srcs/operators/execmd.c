/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:33:02 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/23 08:43:44 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

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
		free(env_path[i]);
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
			break ;
	}
	return (path);
}

static DIR	*cmd_checks(t_table *tab, t_list *cmd, char ***s, char *path)
{
	DIR		*dir;
	t_node	*n;

	dir = NULL;
	n = cmd->content;
	if (n && n->cmd)
		dir = opendir(*n->cmd);
	if (n && n->cmd && ft_strchr(*n->cmd, '/') && !dir)
	{
		*s = ft_split(*n->cmd, '/');
		n->path = ft_strdup(*n->cmd);
		free(n->cmd[0]);
		n->cmd[0] = ft_strdup(s[0][ft_mx_len(*s) - 1]);
	}
	else if (!is_builtin(n) && n && n->cmd && !dir)
	{
		path = ms_getenv("PATH", tab->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		n->path = find_command(*s, *n->cmd, n->path);
		if (!n->path || !n->cmd[0] || !n->cmd[0][0])
			chk_error(NCMD, *n->cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_table *tab, t_list *cmd, char **s, char *path)
{
	DIR		*dir;
	t_node	*n;

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
	ft_mx_free(&s);
}

void	*execmd(t_table *tab, t_list *cmd)
{
	int		fd[2];
	char	*path;

	get_cmd(tab, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (chk_error(PIPERR, NULL, 1));
	if (!chk_fork(tab, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_node *)cmd->next->content)->infile)
		((t_node *)cmd->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_node *)cmd->content)->infile > 2)
		close(((t_node *)cmd->content)->infile);
	if (((t_node *)cmd->content)->outfile > 2)
		close(((t_node *)cmd->content)->outfile);
	return (NULL);
}
