/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:37 by gehebert          #+#    #+#             */
/*   Updated: 2022/12/07 21:30:37 by gehebert         ###   ########.fr       */
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



t_table 	*token_nodes(t_table *tab, char **cmd)	/* call by parse_  <<(token_ized)	*/
{
	int id;		// node_id
	int tk_len;		// 
		// t_token *token;	// frmd token instanc



		// 		take some of node (remove them) and 
		//		place them at the right place cmd[0], cmd[len]
		//		then wrsap the token tk_id ++ , nodes --	
	id = 0; 
	tk_len = ft_mx_len(cmd);
	while (id != tk_len)
	{
		mx_display_str(cmd[id]);
		id++;
	}
	// tab->cmds >> t_token	*token;
		// token->id 	(int)
		// token->cmd	(char**)
		// token->path	(**char)
		// token->endtype	(int)
		// token->infile :: token->outfile 
		// token->tkn_len	(int)
	// needed to token command
	
	printf("DEBUG : token_nodes cmds [0][0] = tk_len = (%d) ::\n", tk_len);

	if (!(cmd[id] || cmd)) 
		return (NULL);
	
		// tab->token->cmd = ft_mx_ext(tab->token->cmd, node);
		// if (ft_strchar_i(node, "<|>"))
		// {
		
		// tab->cmds[tab->token->id] = ft_mx_dup(cmd);
		// tab->token->id++;
		// printf("DEBUG : token_nodes[%d]::\n", tab->token->id);
		// printf("DEBUG : token_cmd[%s]::\n", *tab->token->cmd);
	
	return (tab);
}

//ls -lt| head -2 |wc -c>> out.txt  
	// if (!(tab->cmds[tkn_id]) && id < tab->tk_num)
	// {
	// 	// mx_display_tab(*tab->cmds);
	// 	mx_display_str(*tab->cmds[id]);
	// }
	// if (tab->tk_num)
	// 	// printf("DEBUG : tk_num = %d:: \n", tab->tk_num);
	// if (*tab->cmds[id] && id < tab->tk_num)
	// {
			// tab->token->id = i;
			// tab->cmds[i] = tab->node;
					// ... // div_token to set end 
					// endtype eval + default 

				// revert from list 
					// need to set first arg => cmd 
					// 			set last arg => endtype
					//	middle arg (if so!) 	
					// cmds[1] = ft_lstlast(cmds[0]);

				// j = 0;
				// if (i == 0 || (tab->node[0] == "|" && *tab->cmds[i + 1] && tab->cmds[i + 1][0]))
			// {
		// tab->token->id = id;
		// // token->cmd = tab->cmds[id];
		// printf("debug:: into tok_node");
		// 	// 	// if (tab->token->cmd)
		// 	// 		// 	mx_display_tab(tab->token->cmd);
		// 	// 		// 		/*	i += args[i][0] == '|';
		// 	// 		// 			ft_lstadd_back(&cmds[0], ft_lstnew(mx_init()));		// mx_start 
		// 	// 		// 			cmds[1] = ft_lstlast(cmds[0]); 
		// 	// 		// 		*/
		// 	// }
		// 	// temp[0] = args;
		// 	//tab->token = get_params(tab, tab->node);//, &i); // params_ ended_ token_
		// 		// token->cmd = cmds[1]->content;
		// 		// token->arg = *temp[1];
		// 		// token->endtype = cmds[1]->content;
		// 		// if (i < 0)
		// 		// 	return (stop_fill(cmds[0], args, temp[1]));
		// 		// if (!args[i])
		// 		// 	break ;
		// id++;
	// }

/*
from parse.c
	fill_node 	=> t_list builder 
		get_trimmed		=> multiple cmd list
				str_trimm_all 	(malloc_machine)	==> trimm_all.c
		mx_init 		=> matrix start
		get_params		=> token_end part (struct mx)
		stop_fill		=> t_list (wrap + free)
*/