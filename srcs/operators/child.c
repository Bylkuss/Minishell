/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:32:42 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/22 21:43:04 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
extern int g_status;

void	child_builtin(t_table *tab, t_token *t)
{
    int l;  //cmd len
	// char **cmd;

    l = ft_strlen(*t->cmd);	
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	//
		printf("DEBUG:@@ chld_bltn :: t->path { %s }\n", t->path); 	//len[%d]", l);
		printf("DEBUG:@@ chld_bltn :: t->cmd { %s }\n", *t->cmd);
		printf("DEBUG:@@ chld_bltn :: cmd_len[%d]\n", ft_mx_len(t->cmd));
	if (!is_builtin(t) && t->cmd)
		execve(t->path, t->cmd, tab->envp);
	// {
	// 	// cmd = ft_split(t->cmd[id], ' ');
	// 	// printf("DEBUG:@@ chk_bltn :: t->cmd[id:%d]\n", id);//t->path); 	//len[%d]", l);
	// 	// printf("DEBUG:@@ chk_bltn :: t->cmd{%s}\n", t->cmd[id]);//t->path); 	//len[%d]", l);
	// 	printf("DEBUG:@@ chld_bltn :: t->path { %s }\n", t->path); 	//len[%d]", l);
	// 	printf("DEBUG:@@ chld_bltn :: t->cmd len (%d) \n", ft_mx_len(cmd)); 
	// }
	else if (t->cmd && !ft_strncmp(*t->cmd, "pwd", l) && l == 3)
		g_status = pwd();
	else if (is_builtin(t) && t->cmd && !ft_strncmp(*t->cmd, "echo", l) && l == 4)
		g_status = echo(t->cmd);
	else if (is_builtin(t) && t->cmd && !ft_strncmp(*t->cmd, "env", l) && l == 3)
	{
		// ft_mx_fd(tab->envp, 1);
		env(tab->envp);
		g_status = 0;
	}
}

static void	*child_redir(t_token *t, int fd[2])
{
    // t_token	*t;

	// t = token;
	printf("DEBUG: TEST child_redir ::welcome!\n");
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
	else if (t->endtype && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (chk_error(DUPERR, NULL, 1));
	printf("DEBUG: TEST child_redir ::byebye!\n");
	close(fd[WRITE_END]);
	return ("");
}

void	*born_child(t_table *tab, t_token *t, int fd[2])
{
    // t_token*t;
	int		l;

	// t = token;
	l = 0;
	if (t->cmd)
		l = ft_strlen(t->cmd[0]);
	printf("DEBUG: born_chld_fork :: t->cmd{%s} \n", *t->cmd);
	child_redir(t, fd);

	close(fd[READ_END]);

	child_builtin(tab, t);
	printf("end_born_child\n");
    // remove token
    // free_cont
	// ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void    exc_fork(t_table *tab, t_token *t, int fd[2])
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

void *chk_fork(t_table *tab, t_token *t, int id, int fd[2])
{
    // t_token *t;
    DIR     *dir;
	// printf("DEBUG: TEST chk_fork \n");
    // t = token;
    dir = NULL;
    if (t->cmd)
        dir = opendir(*t->cmd);
    if (t->infile == -1 || t->outfile == -1)
        return (NULL);
    if ((t->path && access(t->path, X_OK) == 0) || is_builtin(t))
		exc_fork(tab, t, fd);
		// printf("DEBUG: GRR.. exc_frk\n");}
    else if (!is_builtin(t) && ((t->path && !access(t->path, F_OK)) || dir))
        g_status = 126;
    else if (!is_builtin(t) && t->cmd)
        g_status = 127;
    if (dir)
        closedir(dir);
	printf("DEBUG: wanna_exit_ _ _ exc_frk\n\n");
    return ("");
}
	// {
		// printf("DEBUG: GRR..NO_BUILTIN exc_frk \n");
	// }