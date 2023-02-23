/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:54:54 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/20 11:07:15 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

extern int g_status;


static int	malloc_len(char const *s1)
{
	int	count;
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (s1 && s1[i])
	{
		squote = (squote + (!dquote && s1[i] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !squote) || (s1[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}

char	*q_trim(char const *s1, int squote, int dquote)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = malloc_len(s1);
	if (!s1 || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]])
	{
		squote = (squote + (!dquote && s1[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || squote) && (s1[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}

  // t_node *init_node(void)
    // {
    //     t_node *node;

    //     node = malloc(sizeof(t_node));
    //     if (!node)
    //         return (NULL);
    //     // tab->node = node;
    //     node->id = 0;
    //     node->cmd = NULL;  
    //     node->path = NULL;
    //     node->xfile = NULL;
    //     node->etype = 0;
    //     node->infile = STDIN_FILENO;
    //     node->outfile = STDOUT_FILENO;
    //     node->nod_len = 0;
    //     return (node);   
  // }

// t_table *init_tab(t_table tab)
// {
//     tab = malloc(sizeof(t_table ));
//     tab->envp = NULL;
//     tab->cmds = NULL ;   
//     tab->cmdl = NULL;
//     tab->token = NULL;
//     tab->node = NULL;
//     tab->refs  = 0;
//     tab->nods = 1;
//     (void) tab->pid;
//     return (tab);
// }

// t_table 	*node_alloc(t_table tab)	/* call by parse_  <<(node_ized)	*/
// {	
// 	int nod_len;		// array width

// 	tab->node->id = 1;
//     printf("DEBUG:: tab->nods = %d\n", tab->nods);
// 	tab->cmds = (char ***)malloc(sizeof(char **) * tab->nods);
//     if (tab->node->id <tab->nods)
//     {
//         while(tab->node->id <= tab->nods) //id tab->nods  
//         {		
//             nod_len = tab->refs[tab->node->id];	
//             tab->cmds[tab->node->id] = (char **)malloc(sizeof(char *) * nod_len);
//             tab->node->id++;
//         }		
//     }
//     else if (tab->node->id == tab->nods)	
//     {
//         nod_len = ft_mx_len(tab->token);  // actual_len == (etype[pos] - old_len)
//         tab->cmds[tab->node->id] = (char **)malloc(sizeof(char *) * nod_len);
//     }
// 	return (tab);
// }

// /*
// main :  init_prompt => get user info to be stock into *p {struct t_dot}   
//         signal      => Global variable to be access anywhere ...
//                 getmypid    => fork process for multiple cmd.
//         init_vars   => split envp.args to stock into tab->envp 
//                 ms_setenv, ms_getenv   ==> signal.c      
//         getprompt   => prompt.c
//         check_args  => parse.c    
// */
