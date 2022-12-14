/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/14 10:25:14 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
// set = endtype*char	count 0++; 

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
	printf("DEBUG: token_count :: strt = [%d]\n", strt);
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

	printf("DEBUG: 		token_count :: \tn = (%d)\n", n);
	return (n); 
}

static t_table *token_fill(t_table *tab, int len, int strt)
{	
	int i;	//node pos
	int id;
	int tk_len;
	
	tk_len = 0;
	i = 0;
	id = tab->token->id;
		printf("DEBUG: token_fill :: ref[strt](%d)::\n", tab->refs[strt]);	
		// printf("DEBUG: token_fill :: strt_pos[%d];; \n", strt);
		// printf("DEBUG: token_fill str {%s} \n", nodes[init]);	
				// if (i <= (tab->refs[pos]))
				// 	printf("DEBUG: token_fill :: NOTready !!!  \n");
				// if (tab->cmds )
				// 	printf("DEBUG: token_fill ::or maybe ready !!!  \n");
				// else
				// 	printf("DEBUG: token_fill :: i dont know!!! !!!  \n");
	// mx_display_tab(tab->node);
	while (id <= tab->tk_num)
	{
		tk_len = tab->refs[strt];
		// printf("DEBUG: token_fill :: t->r[] = (%d) \n", tab->refs[strt]);	
		// printf("DEBUG: token_fill :: tk_len = (%d) \n", tk_len);	
		while (i <= (tk_len))
		{
			tab->cmds[id] = ft_mx_ext(tab->cmds[id], tab->node[i]);
			printf("DEBUG: token_fill cmds[%d] node[%d] {%s} \n", id, i, tab->node[i]);	
			i++;
			// pos++;
		}
		strt = id;
		id++;
	}
	// tab->cmds[id] = ft_mx_ext(tab->cmds[id], "\0");
		// printf("DEBUG: token_fill_ end = %d\n", ft_mx_len(tk_cmd));	
		// printf("DEBUG: token_fill_cmd_len_check = (%d) \n", ft_mx_len(tk_cmd));	
	return (tab);
}

	// 	   ls -lt| head -2 |wc -c>> out.txt   
   
// >> node[x]  >> set  >> tab  >> tkn_id  (focus id)
t_table	 *div_token(const char *s, char *set, t_table *tab, int tkn_id) // call by parse>split_all
{
	t_token	*token;			// token sub_split by endtype
	char **tkn;
	int 	pass_len;		// pos to start
	
	token = tab->token;
	pass_len = 0;

		printf("DEBUG: div_token_ parse_ tkn_id = %d\n", tkn_id);
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
	
	if ((tkn_id < token->id))// start at zero < token->id start at 1
	{
		token->tk_len = token_count(tab->node, set, pass_len);	// how many node into this token
		// printf("DEBUG: token_count len (%d) \n", token->tk_len);		
			// pass_len = tab->refs[tab->token->id];	
			// printf("DEBUG:  refs[tkn_id:%d] =>it is ==> past_len[pos:%d]\n", tkn_id, pass_len);
			// printf("DEBUG:  token->id:%d => supp ==> t->refs[tkn_id:%d]\n", token->id, tab->refs[tkn_id]);
			// printf("DEBUG:  t->t->id:%d] => supp ==> t->refs[t->t->id:%d]\n", tab->token->id, tab->refs[tab->token->id]);
			// printf("DEBUG:  refs[tk_num:%d] => supp ==> past_len[pos:%d]\n", tab->token->id, tab->refs[tab->token->id]);
			// token->tk_len =	token->tk_len - pass_len;
			// tab->token->cmd check!!

		tkn = (char **)malloc(sizeof(char *) * (token->tk_len + 2)); 
		if (!(tkn))
			return (NULL);

		tab = token_fill(tab, token->tk_len, pass_len);	
		// tab->token->cmd = ft_mx_dup(tkn);
		// tab->token->id++;	
	}	
		

		// pass_len = ft_mx_len(tab->token->cmd);
		// printf("DEBUG: div_token:: tab->token->cmd(%d)len\n", pass_len);
		// mx_display_tab(token->cmd);
	printf("DEBUG: div_token:: end...\n");
	return (tab);    
}
  //   ls  -lta | wc -l >> out.txt   
  //   ls -lt|head -2| wc -l >> out.txt   
//	
	// tab->token->tk_len = ft_mx_len(tkn);
	
		// t_fill reciv array *str endtyp
		//		**tkn << tab->cmds >> sub_split / endtype char
	
		///		ft_mx_ext ... 
		//		
		///;
			// tab->token = token_etype(tab)
			// if (*tkn)
			// {
			// 	tab->node[tk_id] = tkn[tk_id];
			// 	tk_id++;		// tab->token->id = 0;		// tab->token->id++;
			// 	while (tk_id < tab->tk_num)
			// 	{
			// 		tab->node[tk_id] = tkn[tk_id];
			// 		tk_id++;
			// 	}
				// mx_display_tab(tkn);
			// }
		/*
			while (nb < tknum)
			{
				token->id = nb;
				token->cmd = aux[0];
				token->endtype = 
			}
			aux ** == tab->node[id][str]] 
			tab->node[token_id] = NULL;
		*/
	// return (tab->cmds[i])
 
/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/