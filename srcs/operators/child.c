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

void	child_builtin(t_table *tab, t_node *n, int l, t_list *cmd)
{
    
	// char **cmd;

    

	// printf("DEBUG:: ___chld_bltn :: cmd_len[%d]\n", t->nod_len);
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	//
	if (!is_builtin(n) && n->cmd)
	{
		// printf("DEBUG::___EXECVE:: chld_bltn :: [id:%d]\n", t->id);//t->path); 	//len[%d]", l);
		execve(n->path, n->cmd, tab->envp);
		  //
			//
			// 	// printf("DEBUG:@@ chk_bltn :: t->cmd{%s}\n", t->cmd[id]);//t->path); 	//len[%d]", l);
			// 	printf("DEBUG:@@ chld_bltn :: t->path { %s }\n", t->path); 	//len[%d]", l);
			// 	printf("DEBUG:@@ chld_bltn :: t->cmd len (%d) \n", ft_mx_len(cmd)); 
	}
	else if (n->cmd && !ft_strncmp(*n->cmd, "pwd", l) && l == 3)
		g_status = pwd();
	else if (is_builtin(n) && n->cmd && !ft_strncmp(*n->cmd, "echo", l) && l == 4)
		g_status = echo(n->cmd);
	else if (is_builtin(n) && cmd && !ft_strncmp(*n->cmd, "env", l) && l == 3)
	{
		ft_mx_fd(tab->envp, 1);
		g_status = 0;
	}
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_node *n;
	n = cmd->content;
	// printf("DEBUG: __child_redir _ID [%d] :: {[i:%d],[o:%d]}\n", t->id, t->infile, t->outfile);
		// printf("DEBUG: __child_redir _FILENO  :: {[i:%d],[o:%d]}\t**\n",  STDIN_FILENO, STDOUT_FILENO);
		// printf("DEBUG: __child_redir _W/R_END :: {[i:%d],[o:%d]}\n\n",  READ_END, WRITE_END);
	if (n->infile != STDIN_FILENO)
	{
		printf("DEBUG: __child_redir ::t->infile !=  t->etype(%d)\n", n->etype);
		if (dup2(n->infile, STDIN_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(n->infile);
	}
	if (n->outfile != STDOUT_FILENO)
	{	
		printf("DEBUG: __child_redir ::t->outfile !=  t->etype(%d)\n", n->etype);
		if (dup2(n->outfile, STDOUT_FILENO) == -1)
			return (chk_error(DUPERR, NULL, 1));
		close(n->outfile);
	}
	else if(cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (chk_error(DUPERR, NULL, 1));
	// if (t->id > 1 && (dup2(fd[READ_END], STDIN_FILENO) == -1))
	// 	return (chk_error(DUPERR, NULL, 1));
	// printf("DEBUG: __child_redir_{etype[%d]} ::byebye!{[i:%d],[o:%d]}\n", t->etype, t->infile, t->outfile);
	close(fd[WRITE_END]);
	return ("");
}

void	*born_child(t_table *tab, t_list *cmd, int fd[2])
{
	t_node	*n;
	int l;

	l = 0;
	n = cmd->content;
	if (n->cmd)
		l = ft_strlen(*n->cmd);
		
	// printf("DEBUG: _born_ _fork :: t->cmd{%s} \n", *t->cmd);
	// printf("DEBUG: _born_ _fork :: t->nod_len[%d] \n", ft_mx_len(t->cmd));
	// printf("DEBUG: _born_ _fork :: t->etype [%d] t->id: %d\n", t->etype, t->id);
	child_redir(cmd, fd);
	close(fd[READ_END]);

	child_builtin(tab, n, l, cmd);
	printf("DEBUG:: END_ _born_ \n");
    // remove node
    // free_cont(t);
	ft_lstclear(&tab->cmdl, free_cont);
	exit(g_status);
}

void    exc_fork(t_table *tab, t_list *cmd, int fd[2])
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
		born_child(tab, cmd, fd);
}

void *chk_fork(t_table *tab, t_list *cmd, int fd[2])
{
 
    DIR     *dir;
	t_node	*n;

	n = cmd->content;
    dir = NULL;
	// printf("\nDEBUG::_TEST chk_frk [id%d] :: infile[%d] + outfile[%d] \n", t->id, t->infile, t->outfile);
    if (n->cmd)
        dir = opendir(*n->cmd);
    if (n->infile == -1 || n->outfile == -1)
        return (NULL);
    if ((n->path && access(n->path, X_OK) == 0) || is_builtin(n))
		exc_fork(tab, cmd, fd);
    else if (!is_builtin(n) && ((n->path && !access(n->path, F_OK)) || dir))
        g_status = 126;
    else if (!is_builtin(n) && n->cmd)
        g_status = 127;
    if (dir)
        closedir(dir);
	printf("DEBUG::: wanna_exit_ _ _ _ _chk_frk __ __ [id:] \n");// t->id);
    return ("");
}
