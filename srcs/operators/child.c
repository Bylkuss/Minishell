/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:32:42 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/16 00:49:40 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
extern int g_status;

void	child_builtin(t_table *tab, t_node *t)
{
    int l;  //cmd len
	char **cmd;

    l = ft_strlen(*t->cmd);	

	printf("DEBUG:: ___chld_bltn :: cmd_len[%d]\n", t->nod_len);
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	//
	if (!is_builtin(t) && t->cmd)
	{
		printf("DEBUG::___EXECVE:: chld_bltn :: [id:%d]\n", t->id);//t->path); 	//len[%d]", l);
		execve(t->path, t->cmd, tab->envp);
		  //
			//
			// 	// printf("DEBUG:@@ chk_bltn :: t->cmd{%s}\n", t->cmd[id]);//t->path); 	//len[%d]", l);
			// 	printf("DEBUG:@@ chld_bltn :: t->path { %s }\n", t->path); 	//len[%d]", l);
			// 	printf("DEBUG:@@ chld_bltn :: t->cmd len (%d) \n", ft_mx_len(cmd)); 
	}
	else if (t->cmd && !ft_strncmp(*cmd, "pwd", l) && l == 3)
		g_status = pwd();
	else if (is_builtin(t) && cmd && !ft_strncmp(*cmd, "echo", l) && l == 4)
		g_status = echo(cmd);
	else if (is_builtin(t) && cmd && !ft_strncmp(*cmd, "env", l) && l == 3)
	{
		ft_mx_fd(tab->envp, 1);
		g_status = 0;
	}
}

static void	*child_redir(t_node *t, int fd[2])
{
    // t_node	*t;

	// t = node;
	printf("DEBUG: __child_redir_{etype[%d]} ::welcome!{[i:%d],[o:%d]}\n", t->etype, t->infile, t->outfile);
	// printf("DEBUG: __child_redir_END::welcome!{[i:%d],[o:%d]}\n",  READ_END, WRITE_END);
	// printf("DEBUG: __child_redir_FILENO::welcome!{[i:%d],[o:%d]}\n",  STDIN_FILENO, STDOUT_FILENO);
	if (t->infile != STDIN_FILENO)
	{
		if (dup2(t->infile, STDIN_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(t->infile);
	}
	if (t->outfile != STDOUT_FILENO)
	{
		if (dup2(t->outfile, STDOUT_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(t->outfile);
	}
	else if (t->etype == 1 && (dup2(fd[WRITE_END], STDIN_FILENO) == -1))
		return (chk_error(DUPERR, NULL, 1));
	// printf("DEBUG: __child_redir ::byebye!, t->etype(%d)\n", t->etype);
	close(fd[WRITE_END]);
	return ("");
}

void	*born_child(t_table *tab, t_node *t, int fd[2])
{
	// int		l;

	// l = 0;
	// if (t->cmd)
	// 	l = ft_strlen(t->cmd[0]);
	
	printf("DEBUG: _born_ _fork :: t->cmd{%s} \n", *t->cmd);
	printf("DEBUG: _born_ _fork :: t->nod_len[%d] \n", ft_mx_len(t->cmd));
	// printf("DEBUG: _born_ _fork :: t->etype [%d] \n", t->etype);
	child_redir(t, fd);
	close(fd[READ_END]);

	child_builtin(tab, t);
	printf("DEBUG:: END_ _born_ \n");
    // remove node
    free_cont(t);
	// ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void    exc_fork(t_table *tab, t_node *t, int fd[2])
{
    pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		chk_error(FORKERR, NULL, 1);
	}
	else if (!pid)
		born_child(tab, t, fd);
}

void *chk_fork(t_table *tab, t_node *t, int fd[2])
{
 
    DIR     *dir;

    dir = NULL;
    if (t->cmd)
        dir = opendir(*t->cmd);
    if (t->infile == -1 || t->outfile == -1)
        return (NULL);
    if ((t->path && access(t->path, X_OK) == 0) || is_builtin(t))
		exc_fork(tab, t, fd);
    else if (!is_builtin(t) && ((t->path && !access(t->path, F_OK)) || dir))
        g_status = 126;
    else if (!is_builtin(t) && t->cmd)
        g_status = 127;
    if (dir)
        closedir(dir);
	printf("DEBUG:\t wanna_exit_ _ _ _ _exc_frk\n");
    return ("");
}
