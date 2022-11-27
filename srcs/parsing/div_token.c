/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/26 19:39:21 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
// set = endtype*char	count 0++; 

static t_token	*tk_endtype(t_table *tab) //, char **a[2])//, int *i) // endtype (int)
{
	t_token *token;
	char ***cmd;
	int id;

	id = 0;
	token = init_token(tab);
	cmd = tab->node; //[id][node[;]
	

	if (tab->node && (tab->tk_num < token->cmd_len) && (token->id < tab->token_len))
	{
		printf("\n\n\n");
		if (tab->cmds[0] == ">" && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
		if (mx[id][cmd][nod] == '>' && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
			token = get_outfile2(token, mx[id]);//nod
		else if (mx[id][cmd][nod] == '>')
			token = get_outfile1(token, mx[id]);//nod
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && 
			a[0][*i + 1][0] == '<')
			m = get_infile2(m, a[1], i);*/
		else if (mx[id][cmd][nod] == '<')
			token = get_infile1(token, mx[id]);	//nod
		else if (mx[id][cmd][nod] != '|')
		// 	m->full_cmd = ft_mx_ext(m->full_cmd, a[1][*i]);
		// else
		{
			//mini_perror(PIPENDERR, NULL, 2);
			// *i = -2;
		}
		return (token);
	}
	mini_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (token);
}

static int	token_count(char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
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
	return (count); //how many end..
}

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
		return (aux);
}

// 	set = {"<",">","|"} :: if(!set) ? end : err //	s = 
t_table 	*div_token(char const *s, char *set, t_table *tab) // call by parse>split_all
{
	char    **tkn;			// token sub_split by endtype
	int 	tk_id;			// focus token
	// int     tk_len; 		// tkn_len = how many token into tab
	int     i[3];

	i[0] = 0;				// set start pos ptr
	i[1] = 0;				// set sub_end pos ptr
	i[2] = 0;				// set end pos ptr
	if (!s)					// s <<  args[i]  << tab->cmds
		return (NULL);
	tk_id = 0;
    tab->tk_num = token_count((char *)s, set, 0);	// how many end
    if (tab->tk_num == -1)
        return (NULL);
    tkn = (char **)malloc(sizeof(char *) * (tab->tk_num + 1)); 
    if (!(*tkn))
	    return (NULL);
	printf("\n\nOK TEST PRE-TOKEN-FILL !!");
	tab->node = token_fill(tkn, s, set, i);	

	tab->token = tk_endtype(tab);






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
		tab->node[tk_id] = NULL;
	}
	while (tk_id < tab->tk_num)
	{
		tab->token->id = tk_id;

		*token->cmd = tab->node;
		// token->endtype = 
		tk_id++;
	}
	// aux ** == tab->node[id][str]] 

    return (tab);    
}

/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/