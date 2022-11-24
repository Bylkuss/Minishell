/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:16:15 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/24 03:20:22 by gehebert         ###   ########.fr       */
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


static t_token	*get_params(t_table *tab, t_token *token) //, char **a[2])//, int *i) // endtype (int)
{
	int id;
	int cmd;	
	int nod;	
	char ***mx;

	mx = NULL;

	nod = 0;
	cmd = 0;
	id = 0;
	mx[id] = tab->cmds;//[cmd][nod];

	if (tab->cmds[cmd][nod] && (nod < token->cmd_len) && (cmd < tab->token_len))
	{
		printf("\n\n\n");
		if (mx[id][cmd][nod] == '>' && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
			token = get_outfile2(token, mx[id]);//nod
		else if (mx[id][cmd][nod] == '>')
			token = get_outfile1(token, mx[id]);//nod
		/*else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
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
	//mini_perror(PIPENDERR, NULL, 2);
	// *i = -2;
	return (token);
}














char	**fill_nodes(t_table *tab, int i)
{
	// t_token	**token;
	// t_list	*cmds[2];
	// token = init_token()
	// cmds[0] = NULL;
	// char	**temp[2];

	// temp[1] = get_trimmed(tab->cmds); /* malloc_machine twin part */
	while (tab->cmds && i < tab->token_len)
	{
		// revert from list 
			// need to set first arg => cmd 
			// 			set last arg => endtype
			//	middle arg (if so!) 	
		// cmds[1] = ft_lstlast(cmds[0]);

		if (i == 0 || (tab->cmds[i][0] == '|' && *tab->cmds[i + 1] && tab->cmds[i + 1][0]))
		{
			// i += args[i][0] == '|';
		//	ft_lstadd_back(&cmds[0], ft_lstnew(mx_init()));		/* mx_start */
		//	cmds[1] = ft_lstlast(cmds[0]);
		}

		// temp[0] = args;
		tab->token = get_params(tab, tab->token);//, &i);
		// token->cmd = cmds[1]->content;
		// token->arg = *temp[1];
		// token->endtype = cmds[1]->content;
		// if (i < 0)
		// 	return (stop_fill(cmds[0], args, temp[1]));
		// if (!args[i])
		// 	break ;
	}
	// ft_mx_free(&temp[1S
	return (tab->node);
}
// check nodes.c/fill_node
//instead of ... 

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
			// tab->token
		}
		return (aux);
}

// 	set = {"<",">","|"} :: if(!set) ? end : err
//	s = 
t_table 	*div_token(char const *s, char *set, t_table *tab) // call by parse>split_all
{
		
		t_token	*token;				// token->len = how many node into token
		char	**tmp;
		int     i[3];				// int     tknum; 
		
		token = tab->token;
		tab->token_len = 0;
		tmp = NULL;
		i[0] = 0;
		i[1] = 0;
		i[2] = 0;
		if (!s)
			return (NULL);
	
    tab->token_len = token_count((char *)s, set, 0);	// how many end
    if (tab->token_len == -1)
        return (NULL);
    tab->node = malloc(sizeof(char *) * (tab->token_len + 1)) ;
	// tab->token_len;
    if (tab->node == NULL)
        return (NULL);
    tab->node = token_fill(tab->node, (char *)s, set, i);
	// mx_display_tab(aux);

	// set get_param 
	
	// tab->node[token->id] = tab->node[token->id];
		// token->id++;
		// tab->token->id = 0;
		// tab->token->id++;
		// while (token->id < tab->token_len)
		// {
		// 	tab->node[token->id] = aux[token->id];
		// 	token->id++;
	// }
		// while (nb < tknum)
		// {
		// 	token->id = nb;
		// 	token->cmd = aux[0];
		// 	token->endtype = 
		// }
	// aux ** == tab->node[id][str]] 
    // tab->node[token_id] = NULL;
    return (tab);    
}

/*
from parse.c /split_all ->
	div_token 	=> token spliter by ending char (<,>,|)
	word_count & ft_fill_array ... no comment!
	*** return table_command : called token !
*/