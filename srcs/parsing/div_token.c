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
// set = endtype*char	count 0++; 
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
{
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
		tab->token
	}
	return (tab);
}

// 	set = {"<",">","|"} :: if(!set) ? end : err
//	s = 
t_table div_token(char const *s, char *set, t_table tab) // call by parse>split_all
{
		/*
			char    **aux;
			int     tknum; // token->len = how many node into token
			int 	nb;
			int     i[3];

			nb = 0;
			i[0] = 0;
			i[1] = 0;
			i[2] = 0;
			if (!s)
				return (NULL);
		//*/
    tknum = token_count((char *)s, set, 0);	// how many end
    if (tknum == -1)
        return (NULL);
    aux = malloc(sizeof(char *) * (tknum + 1)) ;
	tab->token_len = tknum;
    if (aux == NULL)
        return (NULL);
    aux = token_fill(aux, (char *)s, set, i);
	token->id = 0;

	tab->node[token_id] = aux[token_id];
	token->id++;
	while (tab->token_len > token_id)
	{
		tab->node[token_id] = aux[token_id];
		token->id++;
	}
		// while (nb < tknum)
		// {
		// 	token->id = nb;
		// 	token->cmd = aux[0];
		// 	token->endtype = 
		// }
	// aux ** == tab->node[id][str]] 
    tab->node[token_id] = NULL;
	
    return (tab);    
}

/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/