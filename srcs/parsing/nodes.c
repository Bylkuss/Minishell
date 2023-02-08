/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:37 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/06 18:13:46 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int  token_len(const char *s)
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

static char	*token_trim_q(const char *s, int squote, int dquote)
{
	int     count;
	int     i[2];
	char    *trimmed;

	i[1] = -1;
	i[0] = 0;
	count = token_len(s);
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

static t_table	*token_mx(t_table *tab)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_mx_dup(tab->cmds[0]);
	while (temp && temp[++j])
	{
		aux = token_trim_q(temp[j], 0, 0); /* malloc machine_short */
		free(temp[j]);
		temp[j] = aux;
	}
	tab->token = temp;
	return (tab);
}
//
//fill 	layer-Z with  row-X _and_  colmn-Y  
t_table 	*node_alloc(t_table *tab)	/* call by parse_  <<(node_ized)	*/
{
	int i;
	int id;			// token_id
	int nod_len;		// array width

	id = 1; 
	i = -1;
	nod_len = tab->refs[tab->node->id];
	
	// printf("DEBUG : start_dup:nod_len(%d)::\n", nod_len);	
	// printf("DEBUG : start_dup:nod_num(%d)::\n", tab->nod_num);
	tab->cmds = (char ***)malloc(sizeof(char **) * tab->nod_num);
 	while( ++i < tab->nod_num)
	{
		while( id <= nod_len)
		{
			nod_len = (tab->refs[id] - nod_len);
			tab->cmds[id] = (char **)malloc(sizeof(char *) * nod_len);
			// tab->node->cmd[id] = (char **)malloc(sizeof(char *) * nod_len);
			id++;
		}
	}			
	// printf("ok ici \n");
	return (tab);
}
//   ls -lta| head -2 |wc -c>> out.txt  
	
// t_table 	*node_alloc(t_table *tab)	/* call by parse_  <<(node_ized)	*/
// {
// 	int i;
// 	int id;			// token_id
// 	int nod_len;		// array width

// 	id = 0; 
// 	i = -1;
// 	nod_len = tab->refs[id];
	
// 	// printf("DEBUG : start_dup:nod_len(%d)::\n", nod_len);	
// 	// printf("DEBUG : start_dup:nod_num(%d)::\n", tab->nod_num);
// 	tab->cmds = (char ***)malloc(sizeof(char **) * tab->nod_num);
// 	// tab->node->cmd = (char **)malloc(sizeof(char **) * tab->nod_num);
//  	while( ++i < tab->nod_num)
// 	{
// 		while( id <= nod_len)
// 		{
// 			tab->cmds[id] = (char **)malloc(sizeof(char *) * nod_len);
// 			// tab->node->cmd[id] = (char **)malloc(sizeof(char *) * nod_len);
// 			id++;
// 		}
// 	}			
// 	printf("ok ici \n");
// 	return (tab);
// }	

/*
from parse.c
	fill_token 	=> t_list builder 
		get_trimmed		=> multiple cmd list
				str_trimm_all 	(malloc_machine)	==> trimm_all.c
		mx_init 		=> matrix start
		get_params		=> node_end part (struct mx)
		stop_fill		=> t_list (wrap + free)
*/