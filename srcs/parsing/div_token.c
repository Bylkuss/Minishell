/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:18 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/17 13:36:50 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	token_count(char *s, char *set, int count)	// set = endtype*char	count 0++; 
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
		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);		// tab->token
	}
	return (aux);
}

	/*	 	set = {"<",">","|"} :: if(!set) ? end : err 		*/
t_table 	*div_token(char const *s, char *set, t_table *tab) // call::parse->split_all
{
		
	char    **tkn;			// token sub_split by endtype
	// int     tk_len; 		// tkn_len = how many token into tab
	int 	tk_id;			// focus token
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
    tkn = malloc(sizeof(char *) * (tab->tk_num + 1)); 
    if (tkn == NULL)
        return (NULL);
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
		mx_display_tab(tkn);
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