/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:37 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/13 09:54:25 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	token get-set */
		// static t_token	*get_params(t_table *tab, char **nodes) //, char **a[2])//, int *i) // endtype (int)
		// {
		// 	int id;
		// 	int cmd;	
		// 	int nod;	
		// 	// char ***mx;
		// 	// mx = NULL;
		// 	// mx[id] = tab->cmds;//[cmd][nod];
		// 	id = 0;
		// 	cmd = 0;
		// 	nod = 0;
		//
		// 	// if (tab->cmds[cmd][nod] && (nod < token->tkn_len) && (cmd < tab->tk_num))
		// 	if (*nodes && (nod < token->tkn_len) && (cmd < tab->tk_num))
		// 	{
		// 		printf("\n\n\n");
		// 		while(tab->n)
		// 		if (mx[id][cmd][nod] == '>' && mx[id][cmd + 1] && mx[id][cmd + 1][nod] == '>')
		// 			token = get_outfile2(token, mx[id]);//nod
		// 		else if (mx[id][cmd][nod] == '>')
		// 			token = get_outfile1(token, mx[id]);
		// 		else if (a[0][*i][0] == '<' && a[0][*i + 1] && 
		// 			a[0][*i + 1][0] == '<')
		// 			m = get_infile2(m, a[1], i);
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
		// 	//mini_perror(PIPENDERR, NULL, 2);
		// 	// *i = -2;
		// 	return (token);
// }


// static int  malloc_len(const char *s)
	// {
	//     int count;
	//     int i;
	//     int dquote;
	//     int squote;

	//     i = 0;
	//     count = 0;
	//     dquote = 0;
	//     squote = 0;
	//     while (s)
	//     {
	//         squote = (squote + (!dquote && s[i] == '\'')) % 2;
	//         dquote = (dquote + (!squote && s[i] == '\"')) % 2; 
	//         if ((s[i] == '\"' && !squote) || (s[i] == '\'' && !dquote)) 
	//             count++;
	//     }
	//     if (squote || dquote)
	//         return (-1);
	//     return (count);
	// }

	// char        *ft_strtrim_all(const char *s, int squote, int dquote)
	// {
	//     int     count;
	//     int     i[2];
	//     char    *trimmed;

	//     i[1] = -1;
	//     i[0] = 0;
	//     count = malloc_len(s);
	//     if (!s || count == -1)
	//         return (NULL);
	//     trimmed = malloc(sizeof(char) * (ft_strlen(s) - count + 1));
	//     if (!trimmed)
	//         return (NULL);
	//     while( s[i[0]])
	//     {
	//         squote = (squote + (!dquote && s[i[0]] == '\'')) % 2;
	//         dquote = (dquote + (!squote && s[i[0]] == '\"')) % 2; 
	//         if ((s[i[0]] != '\"' || squote) && (s[i[0]] != '\'' || dquote) \
	//             && ++i[1] >= 0)
	//             trimmed[i[1]] = s[i[0]]; 
	//         i[0]++;
	//     }
	//     trimmed[++i[1]] = '\0';
	//     return (trimmed);
	// }

	// t_table	*get_trimmed(t_table *tab)
	// {
	// 	char	**temp;
	// 	char	*aux;
	// 	int		j;

	// 	j = -1;
	// 	temp = ft_mx_dup(tab->cmds[0]);
	// 	while (temp && temp[++j])
	// 	{
	// 		aux = ft_strtrim_all(temp[j], 0, 0); /* malloc machine_short */
	// 		free(temp[j]);
	// 		temp[j] = aux;
	// 	}
	// 	tab->node = temp;
	// 	return (tab);
// }

char *node_padd(char *input, char *meta)
{
    char *srcs; //  start part str
    char *tmp;  //  sub str
    char *dest; //  end part str
    int p[4];   //ptr pos start/pos/end

    p[2] = 0;
    p[3] = 0;
    p[1] = ft_strchar_i(input, meta); // ret (index found charset into str
    if (p[1] == -1)
        return (input);
    else
    {
        p[0] = p[1] - 1;
        p[2] = p[1] + 1;
        p[3] = ft_strlen(input);
        // printf("the padd p[3] len [%d] \n", p[3]);
        if ((input[p[1] + 1]) == (input[p[1]]))   // twin chk ! 
            p[2] = p[1] + 2;
        // printf("DEBUG : type_check :[%d]: %s \n\n", p[3], input);
        srcs = ft_substr((const char *)input, 0, (p[3] - (p[3] - p[1]))); 
        // printf("DEBUG :: srcs_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);
        tmp  = ft_substr((const char *)input, p[1] , p[2] - p[1]); 
        // printf("DEBUG :: tmp_check [%ld] ::%s: \n",ft_strlen(tmp), tmp);
        dest = ft_substr((const char *)input, p[2] , p[3] - p[2]); 
        // printf("DEBUG :: dest_check [%ld] ::%s: \n",ft_strlen(dest), dest);
        if (input[p[0]] != 32)// tmp -1
            tmp = ft_strjoin(" ", tmp); //add spece before
        if (input[p[2]] != 32) //tmp + 1
            tmp = ft_strjoin(tmp, " ");  //add space after
        srcs = ft_strjoin(srcs, tmp);
        input = ft_strjoin(srcs, dest);
    } 
    return(input);
}

char *type_check(char *input, char *meta)
{
    char *srcs; //  start part str
    char *res;  //  sub str
    char *tmp;
    char *dest; //  end part str
    int p[4];   //ptr pos start/pos/end
    int padd;   // detected

        res = "\0";
        padd = 0;          
        p[2] = 0; //index ptr count 
        p[1] = 0;
        p[3] = ft_strlen(input);
        // printf("type_check:: str_end_p[3] = %d\n", p[3]);
        while (padd == 0)
        {
            p[1] = ft_strchar_i(input, meta); // ret (index found charset into str
            if (p[1] == -1)
            {
                // printf("bye\n");
                padd = 1;
                break ;
            }
            p[0] = p[1] - 1;
            p[2] = p[1] + 1;
            if ((input[p[1] + 1]) == (input[p[1]]))   // twin chk ! 
                p[2] = p[1] + 2;
                
            srcs = ft_substr((const char *)input, 0, (p[3] - (p[3] - p[0]))); //bfore endtype
            // printf("DEBUG :: srcs_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);
            tmp = ft_substr((const char *)input, p[0] , p[2] - p[0]); //etype pad
            // printf("DEBUG :: tmp_check [%ld] ::%s: \n",ft_strlen(tmp), tmp);
            dest = ft_substr((const char *)input, p[2] , p[3] - p[2]); // left
            // printf("DEBUG :: dest_check [%ld] ::%s: \n",ft_strlen(dest), dest);
            res = ft_strjoin(res, srcs);
            if (p[1] && (input[p[0]] != 32) || (input[p[2]] != 32))
                tmp = node_padd(tmp, meta);
            res = ft_strjoin(res, tmp);
            // printf("DEBUG oo res_check[%ld] ::%s: \n",ft_strlen(res), res);
            input = dest;

        }
        input = ft_strjoin(res,dest);
        // printf("DEBUG oo output_check [%ld] ::%s: \n",ft_strlen(input), input);
        return(input);
}



t_table 	*token_nodes(t_table *tab, char **cmd, int tkn_id)	/* call by parse_  <<(token_ized)	*/
{
	int id;		// node_id
	int tk_len;		// 
	// char ***tkn_cmds;
		// t_token *token;	// frmd token instanc

		// 		take some of node (remove them) and 
		//		place them at the right place cmd[0], cmd[len]
		//		then wrsap the token tk_id ++ , nodes --	
		// tab->cmds >> t_token	*token;
			// token->id 	(int)
			// token->cmd	(char**)
			// token->path	(**char)
			// token->endtype	(int)
			// token->infile :: token->outfile 
			// token->tkn_len	(int)
		// needed to token command
	id = 0; 
	if (!(cmd[id] || cmd)) 
		return (NULL);
	*tab->cmds = (char **)malloc(sizeof(char *) * tab->tk_num + 1);
			// printf("DEBUG : start_dup:tkn_id[%d]::\n", tkn_id);	
			printf("DEBUG : start_dup:tk_num[%d]::\n", tab->tk_num);
			// printf("DEBUG : pre_dup:token_id[%d]::\n", tab->token->id);	
	printf("DEBUG: token_nodes ::t->t->id[%d] ::tkn_id[%d]\n", tab->token->id, tkn_id);
	tk_len = ft_mx_len(cmd);
	printf("DEBUG: token_nodes ::id[%d]::tk_len(%d)::\n\n", id, tk_len);
	
	if ((tab->cmds[tkn_id]) != NULL)
	{
		printf("yeah!, welcome!(%d) \n",ft_mx_len(tab->cmds[tkn_id]));
		tab->cmds[tkn_id] = ft_mx_dup(cmd);
		// while(id <= tk_len)
		// {
			// tab->cmds[tkn_id] = ft_mx_ext(tab->cmds[tkn_id], cmd[id]);
			// printf("cmd[%d] => ::%s::\n", id, cmd[id]);
			// id++;
		// }
	}
	else 
		printf("sorry!, try again!\n");
	
	// tk_len = ft_mx_len(tab->cmds[tab->token->id]);	
	// printf("DEBUG : token_nodes tab->cmds(%d) len:: \n", tk_len);
		// tok_cmds = ft_mx_dup(cmd);
		// }
		// else 
		// {
		// 	printf("DEBUG : error :cmds[tkn_id]:[%d]::\n", tkn_id);	
		// 	return (NULL);
			
		// }
		// while (id != tk_len)
		// {
		// 	mx_display_str(tab->token->cmd[id]);
		// 	id++;
		// }
	tab->token->id++;
	printf("DEBUG : exit:token_id[%d]::\n", tab->token->id);
	return (tab);
}

	//   ls -lta| head -2 |wc -c>> out.txt  
		

/*
from parse.c
	fill_node 	=> t_list builder 
		get_trimmed		=> multiple cmd list
				str_trimm_all 	(malloc_machine)	==> trimm_all.c
		mx_init 		=> matrix start
		get_params		=> token_end part (struct mx)
		stop_fill		=> t_list (wrap + free)
*/