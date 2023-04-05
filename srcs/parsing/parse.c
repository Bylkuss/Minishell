/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/21 15:25:22 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static char	**split_all(t_table *tab, char **aux)
{
	int		i;
	int		quotes[2];
	char	**sub;

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	while (aux && aux[++i])
	{
		aux[i] = expand_vars(aux[i], -1, quotes, tab);
		aux[i] = expand_path(aux[i], -1, quotes, ms_getenv("HOME", tab->envp,
					4));
		sub = div_str(aux[i], "<|>");
		ft_mx_rpl(&aux, sub, i);
		i += ft_mx_len(sub) - 1;
		ft_mx_free(&sub);
	}
	return (aux);
}

static void	*parse_args(t_table *tab, char **aux)
{
	int	is_exit;
	int	id;

	is_exit = 0;
	tab->cmdl = get_node(split_all(tab, aux), -1);
	id = ft_lstsize(tab->cmdl);
	g_status = builtins(tab, tab->cmdl, &is_exit);
	while (id-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (tab->cmdl && is_exit)
	{
		ft_lstclear(&tab->cmdl, free_cont);
		return (NULL);
	}
	return (tab);
}

void	*check_args(char *input, t_table *tab)
{
	t_node	*n;
	char	**aux;

	if (!input)
		return (NULL);
	if (input[0] != '\0')
		add_history(input);
	aux = init_split(input, " ");
	free(input);
	if (!aux)
	{
		chk_error(QUOTE, NULL, 1);
		return ("");
	}
	tab = parse_args(tab, aux);
	if (tab && tab->cmdl)
		n = tab->cmdl->content;
	if (tab && tab->cmdl && n && n->cmd && ft_lstsize(tab->cmdl) == 1)
		tab->envp = ms_setenv("_", n->cmd[ft_mx_len(n->cmd) - 1], tab->envp, 1);
	if (tab && tab->cmdl)
		ft_lstclear(&tab->cmdl, free_cont);
	return (tab);
}
/*
from check.c
    check_args  => take input to be init_split to build table command
    init_split   => will do that init_split into a tab **       ==> init_split.c
    parse_args  => call fill_token  return *p (list-> p.cmds)    ==> tokens.c
    split_all   =>  node's alternate end if it's not! 
                    div_node  ('<','>','|')                    ==> divide.c
                    expand_vars & expand_path                   ==> expand.c
    *** so in my mind a node is : CMD + ARG + END 
    *** in fact ARG is facultative
    ls -lt -a| head -3|wc -w>>out.txt
    ls -lt>>popox.txt  
*/
