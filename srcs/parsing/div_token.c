/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/06 13:25:23 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

// /*	token get-set */
int	set_endtype(t_table *tab, char *etype) //, char **a[2])//, int *i) // endtype (int)
{
	int type;	// int cmd;	
	
	type = 0;	// cmd = 0;
	if (ft_strcmp(etype, "<<") == 0)
		tab->token->endtype = INF2_END; // # 5 	//  token = get_infile2(token, token->cmd[id], i);
	else if (ft_strcmp(etype, "<") == 0)
		tab->token->endtype = INF1_END;		// token = get_infile1(token, token->cmd[id]);
	else if (ft_strcmp(etype ,">>") == 0)
		tab->token->endtype = OUTF2_END;	// token = get_outfile2(token, token->cmd[id]);
	else if (ft_strcmp(etype ,">") == 0)
		tab->token->endtype = OUTF1_END;  	// token = get_outfile1(token, token->cmd[id]);
	else if (ft_strcmp(etype ,"|") == 0)
		tab->token->endtype = PIPE_END;		// exec_custom???
	else //if (ft_strcmp(etype ,"@") == 0)
		tab->token->endtype = DEAD_END;     
	
	return (tab->token->endtype);
}

//char ** tab->node, token->id, endtype (int)
t_token	*get_token(t_table *tab, t_token *token, int id)  
{
	int typ;	
	int nod;	
	int i;
		
	typ = 0;
	nod = 0;
	i = -1;

	if ((tab->token->id) && id <= tab->tk_num && tab->cmds[id])
	{
		while(id <= tab->tk_num) //if
		{
			tab->token->id = id;
			nod = tab->refs[tab->token->id];
			tab->token->cmd = ft_mx_ext(tab->token->cmd, *tab->cmds[id]);
			tab->token->endtype = set_endtype(tab, tab->node[nod]);	
			printf("DEBUG:: Get_token t->t->id [%d] [refs:%d]\n", tab->token->id, nod);
			printf("DEBUG:: Get_token:: endtype [%d] \n", tab->token->endtype);
		
			while(++i < nod)
			{
				if (set_endtype(tab, tab->node[i]) > 1)	
				{
					tab->token->ofile = ft_strjoin(tab->token->ofile, tab->node[i + 1]);	
					i++;
					break;
				}			
				tab->token->full = ft_strjoin(tab->token->full, tab->cmds[id][i]);
				if ((i + 1) < (nod))
					tab->token->full = ft_strjoin(tab->token->full, " ");

			}
			if (tab->token->endtype == 2 || tab->token->endtype == 3)
				tab->token->ofile = ft_strjoin(tab->token->ofile, tab->node[nod + 1]);
			// if (tab->token->endtype == 4)
			// 	tab->token->ofile = ft_strjoin(tab->token->ofile, tab->node[nod + 1]);
			
			printf("DEBUG: Get_token->endtype [%d]\n", tab->token->endtype);
			printf("DEBUG: Get_token->ofile {%s} \n", tab->token->ofile);
			printf("DEBUG: token->full __%s__\n\n", tab->token->full);

			
			i = -1;		
			if (tab->token->endtype == 2 )// || tab->token->endtype == 3)
				token = get_outfile1(token, tab);
			else if (tab->token->endtype == 3)
				token = get_outfile2(token, tab);
			else if (tab->token->endtype == 4)
				token = get_infile1(token, tab);
			else if (tab->token->endtype == 5)
				token = get_infile2(token, tab);   
			id++;
			tab->token->endtype = -1;
		}
	}
	// ls > popov.txt
	// wc < toto.txt 
			// tab->token->cmd[nod - 1] = NULL;	
			// got to do token with tab data
			// 		- token->id = 1; parce que! tab->cmds[id]...
			//		- token->cmd** = {"","",""} start with cmd[0] to exec
			//		-				=  follow by args (if so) cmd[1]
			//		-				= cmd[eot] : eot= endoftoken - aka endtype
			//		redir set by endtype
			//		-	dead_end :normal ending close fd/free/exit (1) ... aka "fit"
		// if (tab->cmds[cmd][nod] && (nod < token->tkn_len) && (cmd < tab->tk_num))
	// tab->token->id = 1;
	return (tab->token);
}

static int	div_count(char **nodes, char *set, int strt)
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

// token_fill : use tab->cmds[] to stack token... former tab->node[]
static t_table *token_fill(t_table *tab, int len, int strt, char **tkn)
{	
	int i;	//node pos
	int id;
	int tk_len;
	
	tk_len = 0;
	i = 0;
	id = 1;
	while (id <= tab->tk_num)
	{
		tk_len = tab->refs[id];
		printf("token_fill => tk_len(%d)\n", tk_len);
		tab->cmds[id] = ft_mx_dup(tkn);
		while (i < (tk_len))
		{
			tab->cmds[id] = ft_mx_ext(tab->cmds[id], tab->node[i]);
			printf("DEBUG: token_fill cmds[%d] node[%d] {%s} \n", id, i, tab->node[i]);	
			i++;
		}
		tab->token->endtype = set_endtype(tab, tab->node[tab->refs[tab->token->id]]);
		if (tab->token->endtype == 0)
			break;		
		else if (tab->token->endtype == 1)
			i++;
		id++;
	}
	return (tab);
}

//
   
t_table	 *div_token(t_table *tab, char *set) // call by parse>split_all
{
	t_token	*token;			// token sub_split by endtype
	char **tkn;
	int 	pass_len;		// pos to start
	int 	tk_id;
	
	token = tab->token;
	pass_len = 0;
	tk_id = 0;
	
	if ((tk_id < tab->tk_num))// start at zero < token->id start at 1
	{
		token->tk_len = div_count(tab->node, set, pass_len);	// how many node into this token
			printf("DEBUG: div_t tk_len (%d) \n", token->tk_len);		
			printf("DEBUG: div_t tk_num (%d) \n", tab->tk_num);		
		tkn = (char **)malloc(sizeof(char *) * (token->tk_len )); 
		if (!(tkn))
			return (NULL);
		tab = token_fill(tab, token->tk_len, pass_len, tkn);	
		// printf("DEBUG: token->cmd[%d] ==> {%s} \n", tk_id + 1, token->cmd[tk_id + 1]);
		// tk_id++;
	}	
	printf("DEBUG: div_token:: end... \t... go for get_token \n\n");
	// tab->token = get_token(tab, token, 1);
		/*
		now tab->cmds[id][cmd[0]] 				char *
		and then so ... tab->cmds[id][cmd[i++]] char *
		*/

	return (tab);    
}
  //   ls -l -t -a| head -2 |wc -c>> out.txt   
  //    ls -lta >> popov.txt    
  // cat < popov.txt
  //   < popov.txt | wc -l 
  //  < popov.txt wc -l | cat > titi2.txt
  //   ls  -lta | wc -l >> out.txt   
  //   ls -lt|head -2| wc -l >> out3.txt  
//    printf("DEBUG: TEST find_command >> path{%s}  \n", path);
 
/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/