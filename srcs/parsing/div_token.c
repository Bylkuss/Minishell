/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/24 20:36:28 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
// set = endtype*char	count 0++; 

static int	token_count(const char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s[i] != '\0')
	{
		if (!ft_strchr(set, s[i]))
		{
			i++;
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				if(!q[1] && (s[i] == '\"' || s[i] != '\0'))
                	q[1] = s[i];
            	q[0] = (q[0] + (s[i] == q[1])) % 2;
            	q[1] *= q[0] != 0;
            	i++;
					// q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
					// q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2; 
					// i++;
			}
			if (q[0])// || q[1])
				return (-1);
		}
		else if (count == 0)
			count = 1;
	}
	printf("DEBUG : into... token_count = %d\n", count);
	return (count); //how many end..
}

// static t_token	*token_params(t_table *tab) //, char **a[2])//, int *i) // endtype (int)
	// {
	// 	t_token *token;
	// 	char **cmd;
	// 	char ***mx;
	// 	int id;

	// 	id = 0;
	// 	// cmd = NULL;
	// 	// token->cmd = tab->node;
	// 	cmd = tab->node; //[id][node[;]
	// 	// cmd = tab->node;

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
	// 			//mini_perror(PIPENDERR, NULL, 2);
	// 			// *i = -2;
	// 		}
	// 		return (token);
	// 	}
	// 	mini_perror(PIPENDERR, NULL, 2);
	// 	*i = -2;
	// 	return (token);
// }

	// set == endtype char_split	i[x] == start_pos/sub_end/end_pos
static char	**token_fill(char **aux, char *s, char *set, int i[3])
{	
	int len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	len = ft_strlen(s);
	// printf("Hello, welcome to Token_Fill\n");
	while (s[i[0]])
	{
		while(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
        	i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2; 
			i[0]++;
		}
		if (i[1] >= len)
        	aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
			// tab->token
		}
		return (aux);
}

// 	set = {"<",">","|"} :: if(!set) ? end : err //	s = 
t_table 	*div_token(char *s, char *set, t_table *tab) // call by parse>split_all
{
		
	char    **tkn;			// token sub_split by endtype
	// int     tk_len; 		// tkn_len = how many token into tab
	int 	tk_id;			// focus token
	int     i[3];

	i[0] = 0;				// set start pos ptr
	i[1] = 0;				// set sub_end pos ptr
	i[2] = 0;	
	if (!s)					// s <<  args[i]  << tab->cmds
		return (NULL);
	tk_id = 0;
	printf("DEBUG : into... div_token\n");	// set end pos ptr
    tab->tk_num = token_count(s, set, 0);	// how many end
	if (tab->tk_num == (-1))
		return (NULL);
    tkn = (char **)malloc(sizeof(char *) * (tab->tk_num + 1)); 
    if (!(*tkn))
	    return (NULL);
	// printf("DEBUG : into div_token ::: %d ::\n", tab->tk_num);
    tkn = token_fill(tkn, (char *)s, set, i);	

	//	**tkn << tab->cmds >> sub_split / endtype char
	//		... so  tkn[tk_id]
	if (*tkn)
	{
		tab->node[tk_id] = tkn[tk_id];
		tk_id++;		// tab->token->id = 0;		// tab->token->id++;
		while (tk_id < tab->tk_num)
		{
			tab->node[tk_id] = tkn[tk_id];
			tk_id++;
		}
		// mx_display_tab(tkn);
	}
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
    return (tab);    
}

/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/