/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/08 11:04:46 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
// set = endtype*char	count 0++; 

static int	token_count(char **nodes, char *set, int tkn)
{
	int		q[2];
	int		i;
	int		n;
	int		etype;	// num ref. etype if not next

	etype = -1;
	n = 0;
	q[0] = 0;
	q[1] = 0;

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

	// printf("DEBUG: token_count :: tkn = %d\n", tkn);
	return (n); //how many end..
}

static char	**token_fill(char **nodes, int len)
{	
	int		init;
	char **tk_cmd;

	init = 0;
	tk_cmd = NULL;//ft_mx_dup(aux);
		// max = ft_mx_len(aux);
		// if (max != 0)
		// 	printf("DEBUG: token->start= %d , first {%s}\n", max, aux[0]);
		// printf("DEBUG: token_fill end = %d \n", len);	
		// printf("DEBUG: token_fill start \n");	
	while (init <= (len ))
	{
		tk_cmd = ft_mx_ext(tk_cmd, nodes[init]);
		printf("DEBUG: token_fill cmd [%d], _%s_ \n", init, tk_cmd[init]);	
		init++;
	}
	// printf("DEBUG: token_fill_ end = %d\n", ft_mx_len(tk_cmd));	
	printf("DEBUG: token_fill_cmd_len_check = (%d) \n", ft_mx_len(tk_cmd));	
	return (tk_cmd);
}


//     ls -lat | wc -l > out.txt    
	// 	ls -lt| head -2 |wc -c>> out.txt   
t_table	 *div_token(const char *s, char *set, t_table *tab, int tkn_id) // call by parse>split_all
{
	// >> node[x]  >> set  >> tab  >> tkn_id  (focus id)
	t_token	*token;			// token sub_split by endtype
	char **tkn;
	
	token = tab->token;
		//	// new div_token purpose : how many token	
		// when call check if token begin or ends
		// 


	if ((tkn_id < token->id))// start at zero < token->id start at 1
	{
		token->tk_len = token_count(tab->node, set, tkn_id);	// how many node into this token
			// printf("DEBUG: div_token_count div_tkn = %d\n", tab->token->tk_len);
			// tab->token->id++;	
			// tab->token->cmd check!!
			// if (ft_mx_len(tab->token->cmd) != 0)


		tkn = (char **)malloc(sizeof(char *) * (token->tk_len + 2)); 
		if (!(tkn))
			return (NULL);

		tkn = token_fill(tab->node, token->tk_len);	
		token->cmd = ft_mx_dup(tkn);
		// mx_display_tab(token->cmd);
	}
	 // printf("DEBUG: div_token :: tk_len = %s\n", tkn[0]);	
		// tab->token->cmd = ft_mx_dup(tkn);
		// printf("DEBUG: div_token :: tkn_str_len = (%d)\n", ft_mx_len(tab->token->cmd));	
		// ft_mx_free(&tkn);
			// tab->token->cmd = (char **)malloc(sizeof(char *) * (tab->tk_num + 1)); 
			// if (!(tab->token->cmd))
			// 	return (NULL);	
			// else
			// {
			// }
	  
			// tab->token->endtype = token_etype(tab);
			// tk_id = token_etype(tab);
				// printf("DEBUG: div_token :: endtype = %d\n", tab->token->endtype);	
	
	printf("DEBUG: div_token :: end...\n");
	tab->token = token;
	
	return (tab);    
}
  //   ls  -lta | wc -l >> out.txt   
  //   ls  | head -2 | wc -l >> out.txt   
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