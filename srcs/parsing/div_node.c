
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/06 18:10:13 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

// /*	node get-set */
int	set_etype(t_table *tab, char *etype) //, char **a[2])//, int *i) // etype (int)
{
	int type;	// int cmd;	
	
	type = 0;	// cmd = 0;
	if (ft_strcmp(etype, "<<") == 0)
		tab->node->etype = INF2_END; // # 5 	//  node = get_infile2(node, node->cmd[id], i);
	else if (ft_strcmp(etype, "<") == 0)
		tab->node->etype = INF1_END;		// node = get_infile1(node, node->cmd[id]);
	else if (ft_strcmp(etype ,">>") == 0)
		tab->node->etype = OUTF2_END;	// node = get_outfile2(node, node->cmd[id]);
	else if (ft_strcmp(etype ,">") == 0)
		tab->node->etype = OUTF1_END;  	// node = get_outfile1(node, node->cmd[id]);
	else if (ft_strcmp(etype ,"|") == 0)
		tab->node->etype = PIPE_END;		// exec_custom???
	else //if (ft_strcmp(etype ,"@") == 0)
		tab->node->etype = DEAD_END;     
	
	return (tab->node->etype);
}

//char ** tab->token, node->id, etype (int)
t_node	*get_node(t_table *tab, t_node *node, int id)  
{
	int typ;	
	int nod_len;	
	int i;
		
	typ = 0;
	i = -1;
	node->nod_len = tab->refs[id];

	// pre-requis builder_node
	if ((tab->nods) && id <= tab->nods && tab->cmds[id])
	{
		// printf("DEBUG:: Get_node t->node->[id:%d] X0X nod_len [%d] by Refs \n", node->id, tab->refs[node->id]);
		while(id <= tab->nods) //if
		{
			node->id = id;
			node->nod_len = tab->refs[node->id];
			printf("DEBUG:: Get_node node->id [%d] [nod_len:%d]\n", id, node->nod_len);
			node->etype = set_etype(tab, tab->token[node->nod_len]);				
			if(++i <= node->nod_len - 1)
			{
				
				printf("DEBUG: TTT->cmds[%d][%d] {__%s__}::len:%d::\n\n", id, i, tab->cmds[id][i], ft_mx_len(tab->cmds[id]));
				tab->node->cmd = ft_mx_ext(tab->node->cmd, tab->cmds[id][i]);
				
			}
			if (node->etype > 1)				// if (set_etype(tab, tab->token[i]) > 1)	
			{
				tab->node->xfile = ft_strdup(tab->token[node->nod_len + 1]);			
				printf("DEBUG: Get_node->xfile {%s} ref + 1\n", tab->node->xfile);
			}
			printf("DEBUG:: Get_node t->node->cmd {%s} \n", *node->cmd);
			if (tab->node->etype >= 2 && tab->node->etype <= 4)
			{
				printf("DEBUG: Get_node->etype [%d]\n", tab->node->etype);
				tab->node->xfile = ft_strdup(tab->token[node->nod_len + 1]);
				printf("DEBUG: Get_node->xfile {%s} \n", tab->node->xfile);
			}		
			i = 0;		
			if (tab->node->etype == 2 )// || tab->node->etype == 3)
				node = get_outfile1(node, tab);
			else if (tab->node->etype == 3)
				node = get_outfile2(node, tab);
			else if (tab->node->etype == 4)
				node = get_infile1(node, tab);
			else if (tab->node->etype == 5)
				node = get_infile2(node, tab);   
			id++;
			tab->node->etype = -1;
			if ((id) > (tab->nods))
				break;
		}
	}
	// ls > popov.txt
	// wc < toto.txt 
			// tab->node->cmd[nod - 1] = NULL;	
			// got to do node with tab data
			// 		- node->id = 1; parce que! tab->cmds[id]...
			//		- node->cmd** = {"","",""} start with cmd[0] to exec
			//		-				=  follow by args (if so) cmd[1]
			//		-				= cmd[eot] : eot= endofnode - aka etype
			//		redir set by etype
			//		-	dead_end :normal ending close fd/free/exit (1) ... aka "fit"
		// if (tab->cmds[cmd][nod] && (nod < node->tkn_len) && (cmd < tab->nod_num))
	// tab->nums = 1;
	return (tab->node);
}

static int	node_count(char **tokens, char *set, int strt)
{
	int		q[2];
	int		i;
	int		n;
	int		etype;	// num ref. etype if not next

	etype = -1;
	n = strt;
	q[0] = 0;
	q[1] = 0;
	// printf("DEBUG: node_count begin :: \tn = (%d)\n", strt);
	while (etype < 0 && (tokens[n]))
	{
		i = 0;
		while (tokens[n] && tokens[n][i] != '\0')
		{		
			if (ft_strchr(set, tokens[n][i]))
				return(n);
			if (!ft_strchr(set, tokens[n][i]))
			{
				while ((!ft_strchr(set, tokens[n][i])) && tokens[n][i] != '\0')
				{ 
						q[0] = (q[0] + (!q[1] && tokens[n][i] == '\'')) % 2;
						q[1] = (q[1] + (!q[0] && tokens[n][i] == '\"')) % 2; 
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

// node_fill : use tab->cmds[] to stack node... former tab->token[]
static t_table *node_fill(t_table *tab, int len, int strt, char **tkn)
{	
	int i;	//token pos
	int id;
	t_node *node;
	
	node = tab->node;	
	node->nod_len = 0;
	i = 0;
	id = 1;

	while (node->id <= tab->nods && i < ft_mx_len(tab->token))
	{
		// tab->node->id = id;
		node->nod_len = tab->refs[node->id]; // - node->nod_len);
		printf("node_fill => node->id[%d]:: nod_len(%d)\n\n", node->id, node->nod_len);
		tab->node->etype = set_etype(tab, tab->token[node->nod_len]);
		printf("DEBUG: TEST >> etype_ _%d_ _  \n", tab->node->etype);
		// tab->cmds[id] = ft_mx_dup(tkn);	
		while (i <  node->nod_len)
		{
			printf("DEBUG: +++ node_fill tab->cmds[%d] token[%d] {%s} \n", node->id, i, tab->token[i]);	
			tab->cmds[id] = ft_mx_ext(tab->cmds[id], tab->token[i]);
			i++;
		}	
			// tab->node->etype = set_etype(tab, tab->token[tab->refs[tab->nums]]);
					// if (tab->node->etype == 0)
					// else if (tab->node->etype == 1)
					// printf("DEBUG: TEST >> ref_  {%s} _  \n", tab->token[tab->refs[id]]);
				// if (i > ft_mx_len(tab->token))
				// 	break;		
		// else
		if (node->id < tab->nods)
			id++;
		else 
			while (i <= ft_mx_len(tab->token))
				i++;

		

		// printf("DEBUG: node_fill _out_reject!! cmds[%d] node[%d] {%s} \n", id, i, tab->token[i]);	
	}
	tab->node = node;
	printf ("DEBUG:: exit _nod_fill\n");
	return (tab);
}

// ls -lt | wc -l >> ut.txt
// ls >> gg.txt
   
t_table	 *div_node(t_table *tab, char *set) // call by parse>split_all
{
	t_node	*node;			// node sub_split by etype
	char **tkn;
	int 	i;		// pos to start
	
	i = 0;
	node = tab->node;
	// node->id = ;
	
	if (node->id <= tab->nods)// start at zero < node->id start at 1
	{
		// node->nod_len = node_count(tab->token, set, 0);	// how many token into this node
		node->nod_len = tab->refs[node->id];
		printf("DEBUG: div_ node->nod_len (%d) \n", node->nod_len);		
		printf("DEBUG: div_ tab->node->id (%d) refs{%s} \n", tab->node->id, tab->token[node->nod_len]);
		// printf("DEBUG: div_ tab->nods (%d) \n", tab->nods);		
		tkn = (char **)malloc(sizeof(char *) * (node->nod_len - 1)); 
		if (!(tkn))
			return (NULL);
		tab = node_fill(tab, node->nod_len, node->nod_len, tkn);	
		// printf("DEBUG: node->cmd[%d] ==> {%s} \n", tab->node->id, node->cmd[node->id]);
		// tk_id++;
	}	
	// printf("DEBUG::div_: t->id[%d] OF nods[%d] << node...\n", node->id, tab->nods);
	printf("DEBUG: div_node:: end... \t... go for get_node \n\n");

	tab->node = node;
	return (tab);    
}
  //   ls -l -t -a| head -2 |wc -c>> out.txt   
  //      
  // cat < popov.txt
  //   < popov.txt | wc -l 
  //  < popov.txt wc -l | cat > titi2.txt
  //   ls  -lta | wc -l >> out.txt   
  //   ls -lt|head -2| wc -l >> out3.txt  
//    printf("DEBUG: TEST find_command >> path{%s}  \n", path);
 
/*
from parse.c /split_all ->
	div_node 	=> node spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called node !
*/