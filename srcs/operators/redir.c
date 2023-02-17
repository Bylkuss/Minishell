/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:28:46 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/22 22:06:40 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
extern int g_status;

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	printf("\nDEBUG: get_fd:: node->file = {%s}\n", path);
	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		chk_error(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		chk_error(NPERM, path, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		chk_error(NPERM, path, 126); 
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1]) //(flags[0] && !flags[1]) 
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1) //(!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}
// t_node	*get_outfile1(t_node *t, int i)
t_node	*get_outfile1(t_node *t, t_table *tab)
{
	char	*nl;
	int		flags[2];
	// int 	id;
	// id = 0;

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected node `newline'";
	// i++;
	if (t->xfile)
		t->outfile = get_fd(t->outfile, t->xfile, flags);
	if (!t->cmd || t->outfile == -1)
	{
		// i = -1;
		if (t->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	// node->etype = 1;
	return (t);
}
// t_node	*get_outfile2(t_node *t, int i)
t_node	*get_outfile2(t_node *t, t_table *tab)
{
	char	*nl;
	int 	id;
	int		flags[2];

	id = 0;
	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected node `newline'";
	// (*i)++;
	if (t->xfile)
		t->outfile = get_fd(t->outfile, t->xfile, flags);
	if (!t->path || t->outfile == -1)
	{
		// *i = -1;
		if (t->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	// node->etype = 2;
	return (t);
}

// t_node	*get_infile1(t_node *t, int i)
t_node	*get_infile1(t_node *t, t_table *tab)
{
	char	*nl;
	int 	id;
	int		flags[2];

	id = 0;
	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error -1- near unexpected node `newline'";
	// (*i)++;
	if (!t->infile && t->xfile)
		t->infile = get_fd(t->infile, t->xfile, flags);
	printf("DEBUG:: infile_1  fd = [%d] t->infile\n", t->infile);
	if (!t->xfile || t->infile == -1)
	{
		// *i = -1;
		if (t->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	// node->etype = 3;
	return (t);
}

// t_node	*get_infile2(t_node *t, int i)
t_node	*get_infile2(t_node *t, t_table *tab)
{
	char	*aux[2];
	char	*nl;
	char	*str[2];
	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	nl = "minishell: syntax error -2- near unexpected node `newline'";
	// (*i)++;
	if (t->path)
	{
		aux[0] = t->cmd[1];
		t->infile = get_here_doc(str, aux);  /*later */
	}
	if (!t->path || t->infile == -1)
	{
		// i = -1;
		if (t->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
	}
	return (t);
}