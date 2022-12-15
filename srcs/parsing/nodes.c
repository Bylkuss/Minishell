/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:37 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/13 09:54:25 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	token get-set */
		// static t_token	*get_params(t_table *tab, char **nodes) //, char **a[2])//, int *i) // endtype (int)
		// {
		// 	int id;
		// 	int cmd;	
		// 	int nod;	
		// 	// char ***mx;
		// 	// mx = NULL;
		// 	// mx[id] = tab->cmds;//[cmd][nod];
		// 	id = 0;
		// 	cmd = 0;
		// 	nod = 0;
		//
		// 	// if (tab->cmds[cmd][nod] && (nod < token->tkn_len) && (cmd < tab->tk_num))
		// 	if (*nodes && (nod < token->tkn_len) && (cmd < tab->tk_num))
		// 	{
		// 		printf("\n\n\n");
		// 		while(tab->n)
		// 		if (mx[id][cmd][nod] == '>' && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
		// 			token = get_outfile2(token, mx[id]);//nod
		// 		else if (mx[id][cmd][nod] == '>')
		// 			token = get_outfile1(token, mx[id]);
		// 		else if (a[0][*i][0] == '<' && a[0][*i + 1] && 
		// 			a[0][*i + 1][0] == '<')
		// 			m = get_infile2(m, a[1], i);
		// 		else if (mx[id][cmd][nod] == '<')
		// 			token = get_infile1(token, mx[id]);	//nod
		// 		else if (mx[id][cmd][nod] != '|')
		// 		// 	m->full_cmd = ft_mx_ext(m->full_cmd, a[1][*i]);
		// 		// else
		// 		{
		// 			//mini_perror(PIPENDERR, NULL, 2);
		// 			// *i = -2;
		// 		}
		// 		return (token);
		// 	}
		// 	//mini_perror(PIPENDERR, NULL, 2);
		// 	// *i = -2;
		// 	return (token);
// }

static int  node_len(const char *s)
{
	int count;
	int i;
	int dquote;
	int squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (s)
	{
		squote = (squote + (!dquote && s[i] == '\'')) % 2;
		dquote = (dquote + (!squote && s[i] == '\"')) % 2; 
		if ((s[i] == '\"' && !squote) || (s[i] == '\'' && !dquote)) 
			count++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}

static char	*node_trim_q(const char *s, int squote, int dquote)
{
	int     count;
	int     i[2];
	char    *trimmed;

	i[1] = -1;
	i[0] = 0;
	count = node_len(s);
	if (!s || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s) - count + 1));
	if (!trimmed)
		return (NULL);
	while( s[i[0]])
	{
		squote = (squote + (!dquote && s[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && s[i[0]] == '\"')) % 2; 
		if ((s[i[0]] != '\"' || squote) && (s[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			trimmed[i[1]] = s[i[0]]; 
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}

static t_table	*node_mx(t_table *tab)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_mx_dup(tab->cmds[0]);
	while (temp && temp[++j])
	{
		aux = node_trim_q(temp[j], 0, 0); /* malloc machine_short */
		free(temp[j]);
		temp[j] = aux;
	}
	tab->node = temp;
	return (tab);
}

t_table 	*token_nodes(t_table *tab)	/* call by parse_  <<(token_ized)	*/
{
	int i;
	int id;			// node_id
	int tk_len;		// array width

	id = 0; 
	i = -1;
	tk_len = tab->refs[id];
	
	// printf("DEBUG : start_dup:tk_len(%d)::\n", tk_len);	
	// printf("DEBUG : start_dup:tk_num(%d)::\n", tab->tk_num);
	tab->cmds = (char ***)malloc(sizeof(char **) * tab->tk_num);
	while( ++i < tab->tk_num)
	{
		while( id <= tk_len)
		{
			tab->cmds[id] = (char **)malloc(sizeof(char *) * tk_len);
			id++;
		}
	}			
	return (tab);
}
//   ls -lta| head -2 |wc -c>> out.txt  
		

/*
from parse.c
	fill_node 	=> t_list builder 
		get_trimmed		=> multiple cmd list
				str_trimm_all 	(malloc_machine)	==> trimm_all.c
		mx_init 		=> matrix start
		get_params		=> token_end part (struct mx)
		stop_fill		=> t_list (wrap + free)
*/