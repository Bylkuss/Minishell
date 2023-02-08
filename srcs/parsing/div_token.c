
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
int	set_endtype(t_table *tab, char *etype) //, char **a[2])//, int *i) // endtype (int)
{
	int type;	// int cmd;	
	
	type = 0;	// cmd = 0;
	if (ft_strcmp(etype, "<<") == 0)
		tab->node->endtype = INF2_END; // # 5 	//  node = get_infile2(node, node->cmd[id], i);
	else if (ft_strcmp(etype, "<") == 0)
		tab->node->endtype = INF1_END;		// node = get_infile1(node, node->cmd[id]);
	else if (ft_strcmp(etype ,">>") == 0)
		tab->node->endtype = OUTF2_END;	// node = get_outfile2(node, node->cmd[id]);
	else if (ft_strcmp(etype ,">") == 0)
		tab->node->endtype = OUTF1_END;  	// node = get_outfile1(node, node->cmd[id]);
	else if (ft_strcmp(etype ,"|") == 0)
		tab->node->endtype = PIPE_END;		// exec_custom???
	else //if (ft_strcmp(etype ,"@") == 0)
		tab->node->endtype = DEAD_END;     
	
	return (tab->node->endtype);
}

//char ** tab->token, node->id, endtype (int)
t_node	*get_node(t_table *tab, t_node *node, int id)  
{
	int typ;	
	int nod;	
	int i;
		
	typ = 0;
	nod = 0;
	i = -1;

	if ((tab->node->id) && id <= tab->nod_num && tab->cmds[id])
	{
		while(id <= tab->nod_num) //if
		{
			tab->node->id = id;
			nod = tab->refs[tab->node->id];
			tab->node->cmd = ft_mx_ext(tab->node->cmd, *tab->cmds[id]);
			tab->node->endtype = set_endtype(tab, tab->token[nod]);	
			printf("DEBUG:: Get_node t->t->id [%d] [refs:%d]\n", tab->node->id, nod);
			printf("DEBUG:: Get_node:: endtype [%d] \n", tab->node->endtype);
		
			while(++i < nod)
			{
				if (set_endtype(tab, tab->token[i]) > 1)	
				{
					tab->node->xfile = ft_strjoin(tab->node->xfile, tab->token[i + 1]);	
					i++;
					break;
				}			
				tab->node->full = ft_strjoin(tab->node->full, tab->cmds[id][i]);
				if ((i + 1) < (nod))
					tab->node->full = ft_strjoin(tab->node->full, " ");

			}
			if (tab->node->endtype == 2 || tab->node->endtype == 3)
				tab->node->xfile = ft_strjoin(tab->node->xfile, tab->token[nod + 1]);
			if (tab->node->endtype == 4)
				tab->node->xfile = ft_strjoin(tab->node->xfile, tab->token[nod + 1]);
			
			printf("DEBUG: Get_node->endtype [%d]\n", tab->node->endtype);
			printf("DEBUG: Get_node->xfile {%s} \n", tab->node->xfile);
			printf("DEBUG: node->full __%s__\n\n", tab->node->full);

			
			i = -1;		
			if (tab->node->endtype == 2 )// || tab->node->endtype == 3)
				node = get_outfile1(node, tab);
			else if (tab->node->endtype == 3)
				node = get_outfile2(node, tab);
			else if (tab->node->endtype == 4)
				node = get_infile1(node, tab);
			else if (tab->node->endtype == 5)
				node = get_infile2(node, tab);   
			id++;
			tab->node->endtype = -1;
		}
	}
	// ls > popov.txt
	// wc < toto.txt 
			// tab->node->cmd[nod - 1] = NULL;	
			// got to do node with tab data
			// 		- node->id = 1; parce que! tab->cmds[id]...
			//		- node->cmd** = {"","",""} start with cmd[0] to exec
			//		-				=  follow by args (if so) cmd[1]
			//		-				= cmd[eot] : eot= endofnode - aka endtype
			//		redir set by endtype
			//		-	dead_end :normal ending close fd/free/exit (1) ... aka "fit"
		// if (tab->cmds[cmd][nod] && (nod < node->tkn_len) && (cmd < tab->nod_num))
	// tab->node->id = 1;
	return (tab->node);
}

static int	div_count(char **tokens, char *set, int strt)
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
	int nod_len;
	
	nod_len = 0;
	i = 0;
	id = 1;
	while (id <= tab->nod_num)
	{
		nod_len = tab->refs[id];
		// printf("node_fill => nod_len(%d)\n", nod_len);
		tab->cmds[id] = ft_mx_dup(tkn);
		while (i < (nod_len))
		{
			tab->cmds[id] = ft_mx_ext(tab->cmds[id], tab->token[i]);
			printf("DEBUG: node_fill cmds[%d] token[%d] {%s} \n", id, i, tab->token[i]);	
			i++;
		}
				// endt = tab->token[tab->refs[id-1]];
		// tab->node->endtype = set_endtype(tab, tab->token[tab->refs[tab->node->id]]);
		tab->node->endtype = set_endtype(tab, tab->token[nod_len]);
		if (tab->node->endtype == 0)
			break;		
		else if (tab->node->endtype == 1)
			i++;
		id++;
	}
	return (tab);
}

//
   
t_table	 *div_node(t_table *tab, char *set) // call by parse>split_all
{
	t_node	*node;			// node sub_split by endtype
	char **tkn;
	int 	pass_len;		// pos to start
	int 	tk_id;
	
	node = tab->node;
	pass_len = 0;
	tk_id = 0;
	
	if ((tk_id < tab->nod_num))// start at zero < node->id start at 1
	{
		node->nod_len = div_count(tab->token, set, pass_len);	// how many token into this node
			printf("DEBUG: div_t nod_len (%d) \n", node->nod_len);		
			printf("DEBUG: div_t nod_num (%d) \n", tab->nod_num);		
		tkn = (char **)malloc(sizeof(char *) * (node->nod_len )); 
		if (!(tkn))
			return (NULL);
		tab = node_fill(tab, node->nod_len, pass_len, tkn);	
		// printf("DEBUG: node->cmd[%d] ==> {%s} \n", tk_id + 1, node->cmd[tk_id + 1]);
		// tk_id++;
	}	
	printf("DEBUG: div_node:: end... \t... go for get_node \n\n");
	// tab->node = get_node(tab, node, 1);
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
	div_node 	=> node spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called node !
*/