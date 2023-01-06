/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/06 09:04:19 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

// /*	token get-set */
int	set_endtype(t_table *tab, char *etype) //, char **a[2])//, int *i) // endtype (int)
{
	int type;	// int cmd;	
	
	type = 0;	// cmd = 0;
	if (ft_strcmp(etype, "<<") == 0)
		tab->token->endtype = INF2_END;    
	else if (ft_strcmp(etype, "<") == 0)
		tab->token->endtype = INF1_END;
	else if (ft_strcmp(etype ,">>") == 0)
		tab->token->endtype = OUTF2_END;
	else if (ft_strcmp(etype ,">") == 0)
		tab->token->endtype = OUTF1_END;          
	else if (ft_strcmp(etype ,"|") == 0)
		tab->token->endtype = PIPE_END;
	else if (ft_strcmp(etype ,"@") == 0)
		tab->token->endtype = DEAD_END;     
	// printf("etype = {%s}", etype);
	// printf("DEBUG: set_ endtype = [%d]\n", tab->token->endtype);
				// printf("\netype = [%d]\n", tab->token->endtype);
			// }
			//  && id < tab->tk_num && tab->cmds[id])

				// while(tab->cmds[id] && id < tab->tk_num)
				// {

				// 	if (mx[id][cmd][nod] == '>' && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
				// 		token = get_outfile2(token, mx[id]);//nod

				// 	else if (mx[id][cmd][nod] == '>')
				// 		token = get_outfile1(token, mx[id]);

				// 	else if (a[0][*i][0] == '<' && a[0][*i + 1] && 	a[0][*i + 1][0] == '<')
				// 		m = get_infile2(m, a[1], i);

				// 	else if (mx[id][cmd][nod] == '<')
				// 		token = get_infile1(token, mx[id]);	//nod

				// 	else if (mx[id][cmd][nod] != '|')
				// 	// 	m->full_cmd = ft_mx_ext(m->full_cmd, a[1][*i]);
				// 	// else
				// 	{
				// 		//mini_perror(PIPENDERR, NULL, 2);
				// 		// *i = -2;
				// 	}
				// 	return (token);
			
				//mini_perror(PIPENDERR, NULL, 2);
				// *i = -2;
	
	return (tab->token->endtype);
}

//char ** tab->node, token->id, endtype (int)
t_table	*get_token(t_table *tab, t_token *token)  
{
	int id;
	int typ;	
	int nod;	
		
	id = 1;
	typ = 0;
	nod = 0;

	if ((tab->token->id) && id < tab->tk_num && tab->cmds[id])
	{
		printf("DEBUG : into... into... get_token\n");	
		while(id < tab->tk_num)
		{
			tab->token->id = id;
			tab->token->cmd = ft_mx_dup(tab->cmds[id]);
			nod = ft_mx_len(tab->cmds[id]);
			// tab->token->endtype = tab->node[tab->refs[id]];
			typ = set_endtype(tab,tab->cmds[id][nod - 1]);
			id++;
		}
		display_tkn(tab);
	}

			// got to do token with tab data
			// 		- token->id = 1; parce que! tab->cmds[id]...
			//		- token->cmd** = {"","",""} start with cmd[0] to exec
			//		-				=  follow by args (if so) cmd[1]
			//		-				= cmd[eot] : eot= endoftoken - aka endtype
			//		redir set by endtype
			//		-	dead_end :normal ending close fd/free/exit (1) ... aka "fit"
		// if (tab->cmds[cmd][nod] && (nod < token->tkn_len) && (cmd < tab->tk_num))

	return (tab);
}

static int	token_count(char **nodes, char *set, int strt)
{
	int		q[2];
	int		i;
	int		n;
	int		etype;	// num ref. etype if not next

	etype = -1;
	n = strt;
	q[0] = 0;
	q[1] = 0;
	// printf("DEBUG: token_count begin :: \tn = (%d)\n", strt);
	while (etype < 0 && (nodes[n]))
	{
		i = 0;
		while (nodes[n] && nodes[n][i] != '\0')
		{		
			if (ft_strchr(set, nodes[n][i]))
				return(n);
			if (!ft_strchr(set, nodes[n][i]))
			{
				while ((!ft_strchr(set, nodes[n][i])) && nodes[n][i] != '\0')
				{ 
						q[0] = (q[0] + (!q[1] && nodes[n][i] == '\'')) % 2;
						q[1] = (q[1] + (!q[0] && nodes[n][i] == '\"')) % 2; 
						i++;
				}
				if (q[0] || q[1])
					return (-1);
			}
			i++;
		}
		n++;
	}
	return (n); 
}

static t_table *token_fill(t_table *tab, int len, int strt, char **tkn)
{	
	int i;	//node pos
	int id;
	int tk_len;
	char *endt;
	
	tk_len = 0;
	i = 0;
	id = tab->token->id;
	while (id <= tab->tk_num)
	{
		tk_len = tab->refs[strt];
		tab->cmds[id] = ft_mx_dup(tkn);
			// printf("DEBUG: token_fill :: t->r[] = (%d) \n", tab->refs[strt]);	
			// printf("DEBUG: token_fill :: tk_len = (%d) \n", tk_len);	
		while (i <= (tk_len))
		{
			tab->cmds[id] = ft_mx_ext(tab->cmds[id], tab->node[i]);
				// printf("DEBUG: token_fill cmds[%d] node[%d] {%s} \n", id, i, tab->node[i]);	
			i++;
		}
		endt = tab->node[tab->refs[id-1]];
		tab->token->endtype = set_endtype(tab, endt);
		if (tab->token->endtype == 3)
			tab->node[i] = ft_strdup((const char *)tab->node[i-1]);
			
			// printf("DEBUG: token_fill :: etype = [%d] \n", tab->token->endtype);	
			// printf(":: endtype = [%d] \n", type);	
		
		strt = id;
		id++;
	}
		// tab->cmds[id] = ft_mx_ext(tab->cmds[id], "\0");
		// printf("DEBUG: token_fill_ end = %d\n", ft_mx_len(tk_cmd));	
		// printf("DEBUG: token_fill_cmd_len_check = (%d) \n", ft_mx_len(tk_cmd));	
	return (tab);
}
   
t_table	 *div_token(t_table *tab, char *set) // call by parse>split_all
{
	t_token	*token;			// token sub_split by endtype
	char **tkn;
	int 	pass_len;		// pos to start
	int 	tk_id;
	
	token = tab->token;
	pass_len = 0;
	tk_id = 0;

		// printf("DEBUG: div_token_ parse_ tkn_id = %d\n", tkn_id);
				// printf("DEBUG: div_token_ div_ token->id = %d\n", token->id);
				// printf("DEBUG: div_token_ token->id[%d] = ref_[%d]\n", tab->token->id, tab->refs[tab->token->id]);
				// printf("DEBUG: div_token_ ref_ tab->token->id = %d\n", tab->refs[tab->token->id]);
					// pass_len = (ft_mx_len(tab->token->cmd) - 1);
					// printf("DEBUG:   ...past_len -> token->cmd = (%d)\n", pass_len);
			// if (tkn_id != 0)
			// {	
			// 	pass_len = tab->refs[tkn_id];	
			// 	ft_mx_free(&tab->token->cmd);
			// }
			// tab->cmds >> t_token	*token;
				// token->id 	(int)
				// token->cmd	(char**)
				// token->path	(**char)
				// token->endtype	(int)
				// token->infile :: token->outfile 
				// token->tkn_len	(int)
			// needed to token command
	// mx_display_tab(tab->node);

	if ((tk_id < token->id))// start at zero < token->id start at 1
	{
		token->tk_len = token_count(tab->node, set, pass_len);	// how many node into this token
		tkn = (char **)malloc(sizeof(char *) * (token->tk_len + 1)); 
		if (!(tkn))
			return (NULL);
		// printf("DEBUG: token_count len (%d) \n", token->tk_len);		
			// pass_len = tab->refs[tab->token->id];	
			// printf("DEBUG:  refs[tkn_id:%d] =>it is ==> past_len[pos:%d]\n", tkn_id, pass_len);
			// printf("DEBUG:  token->id:%d => supp ==> t->refs[tkn_id:%d]\n", token->id, tab->refs[tkn_id]);
			// printf("DEBUG:  t->t->id:%d] => supp ==> t->refs[t->t->id:%d]\n", tab->token->id, tab->refs[tab->token->id]);
			// printf("DEBUG:  refs[tk_num:%d] => supp ==> past_len[pos:%d]\n", tab->token->id, tab->refs[tab->token->id]);
			// token->tk_len =	token->tk_len - pass_len;
			// tab->token->cmd check!!

		

		tab = token_fill(tab, token->tk_len, pass_len, tkn);	
		// tk_id++;
	}	
	printf("DEBUG: div_token:: end...\n");
	return (tab);    
}
  //   ls -lt| head -2 |wc -c>> out.txt   
  //   ls  -lta | wc -l >> out.txt   
  //   ls -lt|head -2| wc -l >> out.txt   
 
/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/