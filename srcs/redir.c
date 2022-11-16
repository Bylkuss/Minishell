/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:28:46 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/13 22:16:00 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
extern int g_status;

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	// if (access(path, F_OK) == -1 && !flags[0])
	// 	mini_perror(NDIR, path, 127);
	// else if (!flags[0] && access(path, R_OK) == -1)
	// 	mini_perror(NPERM, path, 126);
	// else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
	// 	mini_perror(NPERM, path, 126);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_mini	*get_outfile1(t_mini *m, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		m->outfile = get_fd(m->outfile, args[*i], flags);
	if (!args[*i] || m->outfile == -1)
	{
		*i = -1;
		if (m->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (m);
}

t_mini	*get_outfile2(t_mini *token, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
		token->outfile = get_fd(token->outfile, args[*i], flags);
	if (!args[*i] || token->outfile == -1)
	{
		*i = -1;
		if (token->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (token);
}

t_mini	*get_infile1(t_mini *m, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		m->infile = get_fd(m->infile, args[*i], flags);
	if (!args[*i] || m->infile == -1)
	{
		*i = -1;
		if (m->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (m);
}

// t_mini	*get_infile2(t_mini *m, char **args, int *i)
// {
// 	char	*aux[2];
// 	char	*nl;
// 	char	*str[2];

// 	str[0] = NULL;
// 	str[1] = NULL;
// 	aux[0] = NULL;
// 	aux[1] = "minishell: warning: here-document delimited by end-of-file";
// 	nl = "minishell: syntax error near unexpected token `newline'";
// 	(*i)++;
// 	if (args[++(*i)])
// 	{
// 		aux[0] = args[*i];
// 		//token->infile = get_here_doc(str, aux);  /*later */
// 	}
// 	if (!args[*i] || m->infile == -1)
// 	{
// 		*i = -1;
// 		if (m->infile != -1)
// 		{
// 			ft_putendl_fd(nl, 2);
// 			g_status = 2;
// 		}
// 	}
// 	return (m);
// }