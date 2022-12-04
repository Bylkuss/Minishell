/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:37 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/03 19:27:32 by gehebert         ###   ########.fr       */
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

t_table	*get_trimmed(t_table *tab)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_mx_dup(tab->cmds[0]);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0); /* malloc machine_short */
		free(temp[j]);
		temp[j] = aux;
	}
	tab->node = temp;
	return (tab);
}
	
		/* call by parse_  <<(token_ized)	*/
t_token	*token_nodes(t_table *tab)	
{
	int i;		// node_id
	// int j;		// ptr pos
	t_token *token;	// frmd token instanc

	token = tab->token;
	i = 0; 
	
	// tab->cmds >> t_token	*token;
		// token->id 	(int)
		// token->cmd	(char**)
		// token->path	(**char)
		// token->endtype	(int)
		// token->infile :: token->outfile 
		// token->tkn_len	(int)
	// needed to token command
	
	if (tab->cmds)
	{
		printf("DEBUG : token_node cmds [0][0] =  ::\n");
		// mx_display_tab(*tab->cmds);
	}
	if (tab->tk_num)
		printf("DUBUG : tk_num = %d:: \n", tab->tk_num);
	while (*tab->cmds[i] && i < tab->tk_num)
	{
			// tab->token->id = i;
			// tab->cmds[i] = tab->node;
					// ... // div_token to set end 
					// endtype eval + default 

				// revert from list 
					// need to set first arg => cmd 
					// 			set last arg => endtype
					//	middle arg (if so!) 	
					// cmds[1] = ft_lstlast(cmds[0]);

				// j = 0;
				// if (i == 0 || (tab->node[0] == "|" && *tab->cmds[i + 1] && tab->cmds[i + 1][0]))
			// {
		tab->token->id = i;
		tab->token->cmd = tab->cmds[i];
		printf("debug:: into tok_node");
			// 	// if (tab->token->cmd)
			// 		// 	mx_display_tab(tab->token->cmd);
			// 		// 		/*	i += args[i][0] == '|';
			// 		// 			ft_lstadd_back(&cmds[0], ft_lstnew(mx_init()));		// mx_start 
			// 		// 			cmds[1] = ft_lstlast(cmds[0]); 
			// 		// 		*/
			// }
			// temp[0] = args;
			//tab->token = get_params(tab, tab->node);//, &i); // params_ ended_ token_
				// token->cmd = cmds[1]->content;
				// token->arg = *temp[1];
				// token->endtype = cmds[1]->content;
				// if (i < 0)
				// 	return (stop_fill(cmds[0], args, temp[1]));
				// if (!args[i])
				// 	break ;
		i++;
	}
	return (tab->token);
}

/*
from parse.c
	fill_node 	=> t_list builder 
		get_trimmed		=> multiple cmd list
				str_trimm_all 	(malloc_machine)	==> trimm_all.c
		mx_init 		=> matrix start
		get_params		=> token_end part (struct mx)
		stop_fill		=> t_list (wrap + free)
*/