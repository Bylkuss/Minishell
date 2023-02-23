/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:31:08 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/21 22:31:09 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

static t_node *init_node(void)
{
    t_node *node;

    node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    // tab->node = node;
    // node->id = 0;
    node->cmd = NULL;  
    node->path = NULL;
    // node->xfile = NULL;
    // node->etype = 0;
    node->infile = STDIN_FILENO;
    node->outfile = STDOUT_FILENO;
    // node->nod_len = 0;
    return (node);   
}


static t_node	*get_params(t_node *node, char **a[2], int *i)
{
	
	if (a[0][*i])
	{
		// etype = set_etype(tab, a[*i]);
		printf("DEBUG:: ID:%d :: str:%s \n", *i, a[0][*i]);
			if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_outfile2(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = get_outfile1(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = get_infile2(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = get_infile1(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->cmd = ft_mx_ext(node->cmd, a[1][*i]);			
		else
		{
			printf("DEBUG::path 1\n");
			chk_error(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	printf("DEBUG::path 2\n");
	chk_error(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

static char	**strtrim(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_mx_dup(args);
	while (temp && temp[++j])
	{
		aux = q_trim(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

static t_list	*stop_fill(t_list *cmdl, char **tkn, char **tmp)
{
	ft_lstclear(&cmdl, free_cont);
	ft_mx_free(&tmp);
	ft_mx_free(&tkn);
	return (NULL);
}

t_list	*get_node(char **tkn, int i)  
{
	t_list 	*cmdl[2];
	char	**tmp[2];
	
	cmdl[0] = NULL;
	tmp[1] = strtrim(tkn);
	printf("DEBUG:: into the beast::  tkn = %d :: \n",ft_mx_len(tkn));
	printf("DEBUG:: into the beast::  tkn = {%s} :: \n", tkn[(ft_mx_len(tkn) - 1)]);
	while(tkn[++i])
	{
		cmdl[1] = ft_lstlast(cmdl[0]);		
		printf("DEBUG:: begin get_node tk_id:%d :: lst_sz : %d\n", i, ft_lstsize(cmdl[1]));
		if( i == 0 || (tkn[i][0] == '|' && tkn[i + 1] && tkn[i + 1][0]))
		{
			i += tkn[i][0] == '|';
			ft_lstadd_back(&cmdl[0], ft_lstnew(init_node()));
			cmdl[1] = ft_lstlast(cmdl[0]);
		}
		tmp[0] = tkn;
			// printf("DEBUG:: pre_params tkn_id = %d tkn = {%s}:: \n", i, tkn[i]);
		cmdl[1]->content = get_params(cmdl[1]->content, tmp, &i);
        // printf("DEBUG:: post_params tkn_id = %d tkn = {%s}:: \n", i, ((t_node *)cmdl[1]->content)->cmd[i]);

        // printf("DEBUG:: post_params tkn_id = %d tkn = {%s}:: \n", i, ((t_node *)cmdl[0]->content)->cmd[i]);
		if (i < 0)
			return (stop_fill(cmdl[0], tkn, tmp[1]));
		if (!tkn[i])
			break;
	}
	ft_mx_free(&tmp[1]);
    ft_mx_free(&tkn);
		// printf("DEBUG:: after_param tkn_id = %d lst %d:: \n", i, ft_lstsize(cmdl[0]));
	return(cmdl[0]);
}