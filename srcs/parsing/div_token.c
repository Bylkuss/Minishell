/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/08 12:35:08 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

// set = endtype*char	count 0++; 
static int	token_count(char *s, char *set, int tkn)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			tkn++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
    
					q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
					q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2; 
					i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else 
			i++;
	}
	printf("DEBUG: token_count :: tkn = %d\n", tkn);
	return (tkn); //how many end..
}

// static t_token	*token_params(t_table *tab) //, char **a[2])//, int *i) // endtype (int)
	// {
	// 	t_token *token;
	// 	char **cmd;
	// 	char ***mx;
	// 	int id;
	// 
	// 	id = 0;
	// 	// cmd = NULL;
	// 	// token->cmd = tab->node;
	// 	cmd = tab->node; //[id][node[;]
	// 	// cmd = tab->node;
	// 
	// 	if (token->cmd && (token->id < token->cmd_len) && (token->id < tab->token_len))
	// 	{
	// 		printf("\n\n\n");
	// 		if (tab->cmds == ">" && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
	// 		if (mx[id][cmd][nod] == '>' && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
	// 			token = get_outfile2(token, mx[id]);//nod
	// 		else if (mx[id][cmd][nod] == '>')
	// 			token = get_outfile1(token, mx[id]);//nod
	// 		else if (a[0][*i][0] == '<' && a[0][*i + 1] && 
	// 			a[0][*i + 1][0] == '<')
	// 			m = get_infile2(m, a[1], i);*/
	// 		else if (mx[id][cmd][nod] == '<')
	// 			token = get_infile1(token, mx[id]);	//nod
	// 		else if (mx[id][cmd][nod] != '|')
	// 		// 	m->full_cmd = ft_mx_ext(m->full_cmd, a[1][*i]);
	// 		// else
	// 		{
	// 			// if (tab->cmds == ">" && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
	// 			// 	token = get_outfile2(token, mx[id]);//nod
	// 			if (*cmd[id] == '>' && cmd  && *cmd[id + 1] == '>')
	// 				tab->token->endtype = 3;	
	// 			// if (mx[id][cmd][nod] == '>' && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
	// 			// 	token = get_outfile2(token, mx[id]);//nod


	// 			else if (*cmd[id] == '>')
	// 				tab->token->endtype = 2;
	// 						// token = get_outfile1(token, mx[id]);//nod
	// 						// else if (a[0][*i][0] == '<' && a[0][*i + 1] && 
	// 						// 	a[0][*i + 1][0] == '<')
	// 						// 	m = get_infile2(m, a[1], i);*/
	// 						// else if (mx[id][cmd][nod] == '<')
	// 						// 	token = get_infile1(token, mx[id]);	//nod

	// 			else if (*cmd[id] != '|')
	// 				tab->token->endtype = 1;
	// 			else if (*cmd[id] != '\0')
	// 				tab->token->endtype = 0;
					
	// 		}
	// 					// 	m->full_cmd = ft_mx_ext(m->full_cmd, a[1][*i]);
	// 					// else
	// 					// {
	// 						//mini_perror(PIPENDERR, NULL, 2);
	// 						// *i = -2;
	// 					// }
	// 					// return (token);
	// 	// }	
	// 	// mini_perror(PIPENDERR, NULL, 2);
	// 	// *i = -2;
	// 	return (tab->token->endtype);
// }

//	
// set == endtype char_split	i[x] == start_pos/sub_end/end_pos
	// static char	**token_fill(char *s, char *set, t_table *tab)
		// {	
		// 	int tk_id;
		// 	// int i;
		// 		// int len;
		// 		// int		q[2];
		// 		// q[0] = 0;
		// 		// q[1] = 0;
		// 		// len = ft_strlen(s);

		// 	// i = 0;
		// 	tk_id = 0;
		// 		// how many token
		// 		// how long token is 
		// 		// which endtype that closeit...
		// 		// printf("DEBUG: token_Fill :: set ::%s::\n", set);
		// 		// printf("DEBUG: token_Fill :: node ::%s::\n", s);
		// 		// printf("DEBUG: token_Fill :: tk_num ::%d::\n", tab->tk_num);

		// 	if (ft_mx_len(*tab->cmds) > 0)
		// 		printf("\ntk_id > 0\n");

		// 	// {

		// 		// add mx_ext str to an arr!

		// 	if(!ft_strchar_i(set, s))
		// 		tab->cmds[tk_id] = ft_mx_ext(*tab->cmds, s);
		// 	// {
		// 	// 	// i++
		// 	// 	printf("DEBUG: token_Fill :: not_end cmds[%d] ::%s::\n", tk_id, *tab->cmds[tk_id]);
		// 	// 	tk_id++;
		// 	// }
		// 	// if(ft_strchar_i(set, s)) 
		// 	// {
		// 	// 	tab->cmds[tk_id] = ft_mx_ext(tab->cmds[tk_id], s);
		// 	// 	printf("DEBUG: token_Fill :: endtype cmds[%d] ::%s::\n", tk_id, *tab->cmds[tk_id]);
		// 	// 	tk_id++;

		// 	// }	
		// 		// }
		// 		// tab->cmds[tk_id] = ft_mx_ext(tab->cmds[tk_id], s);
		// 		// mx_display_tab(tab->cmds[tk_id]);
		// 		return (tab->cmds[tk_id]);
		// 			// *tab->cmds[tk_id] = s;


		// 			// while (s)
		// 			// {

		// 				// i[1] = i[0];
		// 				// while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		// 				// {
		// 				// 	q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
		// 				// 	q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2; 
		// 				// 	i[0]++;
		// 				// }
		// 				// if (i[1] >= len)
		// 				// 	aux[i[2]++] = "\0";
		// 				// else
		// 				// 	aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
		// 				// 	// tab->token
		// 				// while (s[i[0]] && i[0] <= len)
		// 				// {
		// 				// 	while(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
		// 				//     	i[0]++;
		// 				// 	i[1] = i[0];
		// 				// 	while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		// 				// 	{
		// 				// 		q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
		// 				// 		q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2; 
		// 				// 		i[0]++;
		// 				// 	}
		// 				// 	if (i[1] >= len)
		// 				//     	aux[i[2]++] = "\0";
		// 				// 	else
		// 				// 		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
		// 				// 		// tab->token
		// 				// 	}
		// 				// mx_display_tab(aux);
//
	// 	}

static char	**token_fill(char **aux, char *s, char *set, int i[3])
{	// set == endtype char_split	i[x] == start_pos/sub_end/end_pos
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2; 
				i[0]++;
			}
		}
		else
			i[0]++;
		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
			// tab->token
	}
	printf("DEBUG: token_fill :: end...\n");
	return (aux);
}

// 	set = {"<",">","|"} :: if(!set) ? end : err //	s = 
char	 **div_token(const char *s, char *set, t_table *tab) // call by parse>split_all
{
		
	char    **tkn;			// token sub_split by endtype
	int tkn_len;
	int 	tk_id;			// focus token

	tk_id = 0;
	tkn_len = 0;
	if (!s)					// s <<  args[i]  << tab->cmds
		return (NULL);
	//
	if (!(tab->tk_num > 0))
	{
		tab->tk_num = token_count((char *)s, set, 1);	// how many end at_least_1
		printf("DEBUG: div_token_count :: tk_num = %d\n", tab->tk_num);
		tab->token->id++;
		tkn = (char **)malloc(sizeof(char *) * (tab->tk_num + 2)); 
		if (!(*tkn))
			return (NULL);
		if (tab->tk_num == (-1))
			return (NULL);
	}
			
	tkn = token_fill(tkn, (char *)s, set, 0);	
	if (!(*tkn))
	    return (NULL);
	printf("DEBUG: div_token :: tkn_str_len = %d\n", ft_mx_len(tkn));	
	printf("DEBUG: div_token :: tk_len = %s\n", tkn[0]);	
			// tab->token->cmd = (char **)malloc(sizeof(char *) * (tab->tk_num + 1)); 
			// if (!(tab->token->cmd))
			// 	return (NULL);	
			// else
			// {
			// mx_display_tab(tkn);
			// }
	  
			// tab->token->endtype = token_etype(tab);
			// tk_id = token_etype(tab);
				// printf("DEBUG: div_token :: endtype = %d\n", tab->token->endtype);	
	
	
	return (tkn);    
}
  //   ls  -lta| wc -l>>out.txt   
 //   ls  -lta | wc -l >> out.txt   

/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/