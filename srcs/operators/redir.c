/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:28:46 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/04 08:48:23 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
extern int g_status;

int	get_fd(int oldfd, char *path, t_token *token)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !token->infile )
		chk_error(NDIR, path, 127);
	else if (!token->infile && access(path, R_OK) == -1)
		chk_error(NPERM, path, 126);
	else if (token->infile && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		chk_error(NPERM, path, 126); 

	if (token->infile && token->outfile)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (token->infile && !token->outfile) //(flags[0] && !flags[1]) 
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!token->infile && oldfd != -1) //(!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_token	*get_outfile1(t_token *token, char **args)
{
	char	*nl;
	// int		flags[2];
	int 	id;
	id = 0;

	// flags[0] = 1;
	// flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	// (*i)++;
	if (args[id][token->tk_len - 1])
		token->outfile = get_fd(token->outfile, *args, token);
	if (!args[id] || token->outfile == -1)
	{
		id = -1;
		if (token->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	token->endtype = 1;
	return (token);
}

t_token	*get_outfile2(t_token *token, char **args)
{
	char	*nl;
	int 	id;
	// int		flags[2];

	id = 0;
	// flags[0] = 1;
	// flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	// (*i)++;
	if (args[++(id)])
		token->outfile = get_fd(token->outfile, *args, token);
	if (!args[id] || token->outfile == -1)
	{
		// *i = -1;
		if (token->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	token->endtype = 2;
	return (token);
}

t_token	*get_infile1(t_token *token, char **args)
{
	char	*nl;
	int 	id;
	// int		flags[2];

	id = 0;
	// flags[0] = 0;
	// flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	// (*i)++;
	if (args[id])
		token->infile = get_fd(token->infile, *args, token);
	if (!args[id] || token->infile == -1)
	{
		// *i = -1;
		if (token->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	token->endtype = 3;
	return (token);
}

t_token	*get_infile2(t_token *token, char **args, int *i)
{
	char	*aux[2];
	char	*nl;
	char	*str[2];
	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		token->infile = get_here_doc(str, aux);  /*later */
	}
	if (!args[*i] || token->infile == -1)
	{
		*i = -1;
		if (token->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
	}
	return (token);
}