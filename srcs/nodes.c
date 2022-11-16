/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:37 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/16 00:08:49 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_mini	*mx_init(void)
{
	t_mini	*m;

	m = malloc(sizeof(t_mini));
	if (!m)
		return (NULL);
	m->full_cmd = NULL;
	m->full_path = NULL;
	m->infile = STDIN_FILENO;
	m->outfile = STDOUT_FILENO;
	return (m);
}

<<<<<<< HEAD
static t_mini	*endtype_token(t_mini *node, char **a[2], int *i)
=======
static t_mini	*get_params(t_mini *m, char **a[2], int *i)
>>>>>>> 0d13ec682b0a3a063dba915085e73ed38623ac74
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			m = get_outfile2(m, a[1], i);
		else if (a[0][*i][0] == '>')
			m = get_outfile1(m, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			m = get_infile2(m, a[1], i);
		else if (a[0][*i][0] == '<')
			m = get_infile1(m, a[1], i);
		else if (a[0][*i][0] != '|')
			m->full_cmd = ft_mx_ext(m->full_cmd, a[1][*i]);
		else
		{
			//mini_perror(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (m);
	}
	//mini_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (m);
}

static char	**get_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_mx_dup(args);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0); // s/d quotes rules
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	(void)  &cmds;
	// ft_lstclear(&cmdc, free_content);
	ft_mx_free(&temp);
	ft_mx_free(&args);
	return (NULL);
}

t_list	*fill_nodes(char **args, int i)
{
	t_token	*token = NULL;
	t_list	*cmds[2];
	char	**temp[2];
	
	// token = init_token()
	cmds[0] = NULL;
<<<<<<< HEAD
	temp[1] = get_trimmed(args); /* clean cut token_part */
=======
	temp[1] = get_trimmed(args);
>>>>>>> 0d13ec682b0a3a063dba915085e73ed38623ac74
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mx_init()));		/* mx_start */
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
<<<<<<< HEAD
		cmds[1]->content = endtype_token(cmds[1]->content, temp, &i);  /* wrap token */
=======
		cmds[1]->content = get_params(cmds[1]->content, temp, &i);
		token->cmd = cmds[1]->content;
		token->arg = *temp[1];
		// token->endtype = cmds[1]->content;
>>>>>>> 0d13ec682b0a3a063dba915085e73ed38623ac74
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_mx_free(&temp[1]);
	ft_mx_free(&args);
	return (cmds[0]);
}