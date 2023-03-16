/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:40:44 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/14 22:40:46 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    space between ... pos[flag]  [0/4]
    flag = {none, all_b4, one_b4, one_a4,all_a4}

*/
// static char *ft_spacer(char* srcs, int* pos[4], int fl)
    // {
    //     // int i;
    //     // int f;
        
    //     // i = 0;
    //     // f = pos[i];

    //     // pos[fl] = {POS = token[pos], FL = space_type } / 0:all_b4(etype) / 1:one_b4(etype) / 2:one_a4(etype) / 3:all_a4(etype)
    //     if (fl > 1)
    //     {
    //         // meaning cut after etype for spc manager
    //         //
    //         /// 2 = set one_space after etype
    //         //
    //         /// 3 = set no_space_end
    //           //printf("DEBUG :: only_1_AP_\n");
    //             // p[2] = p[1] + 1;
    //             // if ((srcs[p[1] + 1]) == (srcs[p[1]]))   // twin chk ! 
    //             //     p[2] = p[1] + 2;
    //             // dest = ft_substr(srcs, 0, p[2]); //bfore etype        
    //             // dest = ft_strjoin(dest, " ");
    //             // rest = ft_strjoin(rest, dest); 
    //             // // //printf("DEBUG ::AP_ rest_check[%ld] ::%s: \n",ft_strlen(rest), rest);
    //             // srcs = ft_substr(srcs, p[2], p[3] - (p[2])); // left          
    //             // // //printf("DEBUG ::AP_ new_src_check[%ld] ::%s: \n",ft_strlen(srcs), srcs); 
    //     }
    //     else
    //     {
    //         // meaning cut before etype ... spc manager
    //         //
    //         /// 0 = set no_space_start
    //         //
    //         /// 1 = set one_space before_etype

    //           //printf("DEBUG :: only_1_AV_\n");
    //             // dest = ft_substr(srcs, 0, p[1]); //bfore etype        
    //             // dest = ft_strjoin(dest, " ");
    //             // rest = ft_strjoin(rest, dest);
    //             // // //printf("DEBUG ::AV_ rest_check[%ld] ::%s: \n",ft_strlen(rest), rest);
    //             // srcs = ft_substr(srcs, p[1] , p[3] - p[1]); // left          
    //             // //printf("DEBUG ::AV_ new_src_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);

    //     }
    //     // while (srcs && (i < pos)
// }

// static char *type_check(char *input, char *meta)
// {
//     char    *srcs;  //  start part str
//     char    *dest;  //  end part str
//     char    *rest;  //  sub str
//     int     p[4];   //  ptr pos start/pos/end   
//     int     fl;     //  spacer_flag

//     p[1] = 0;
//     rest = "\0";
//     srcs = ft_strdup(input);    
//     while (ft_strlen(srcs) > 1 && p[1] != -1) 
//     {
//         p[1] = ft_strchar_i(srcs, meta);
//         if (p[1] == -1)
//             break;//padd = 1;
//         else if (p[1] == 0)
//             srcs = ft_strjoin(" ", srcs);
//         p[3] = ft_strlen(srcs);      
//         if ((p[1]) && ((srcs[p[1] - 1] != 32)))
//         {

//             dest = ft_substr(srcs, 0, p[1]); //bfore etype        
//             dest = ft_strjoin(dest, " ");
//             rest = ft_strjoin(rest, dest);
//             srcs = ft_substr(srcs, p[1] , p[3] - p[1]); // left          
//                     /// ft_spacer(char *srcs, pos = p[1]*, int fl) only_one spc before...
//                     // input = ft_spacer(input, p[1], 1); //fl = 1
//                     // //printf("DEBUG :: only_1_AV_\n");    
//                     // //printf("DEBUG ::AV_ rest_check[%ld] ::%s: \n",ft_strlen(rest), rest);
//                     // //printf("DEBUG ::AV_ new_src_check[%ld] ::%s: \n",ft_strlen(srcs), srcs);
//         }    
//         else if ((input[p[1] + 1] != 32) && (p[1] + 1 != p[1]))
//         {
//             p[2] = p[1] + 1;
//             if ((srcs[p[1] + 1]) == (srcs[p[1]]))   // twin chk ! 
//                 p[2] = p[1] + 2;
//             dest = ft_substr(srcs, 0, p[2]); //bfore etype        
//             dest = ft_strjoin(dest, " ");
//             rest = ft_strjoin(rest, dest); 
//             srcs = ft_substr(srcs, p[2], p[3] - (p[2])); // left          
//                 //      // only _one spc after
//                 // input = ft_spacer(input, p[1], 2);  // fl = 2
//                 // //printf("DEBUG :: only_1_AP_\n");
//                 // //printf("DEBUG ::AP_ rest_check[%ld] ::%s: \n",ft_strlen(rest), rest);
//                 // //printf("DEBUG ::AP_ new_src_check[%ld] ::%s: \n",ft_strlen(srcs), srcs); 
//         }   
//         else
//             break;     
//     }
//     rest = ft_strjoin(rest, srcs);         // input = dest; 
//     input = ft_strdup(rest);         // input = dest;
//     //printf("DEBUG::  NEW_input_[%ld]_{%s}_\n",ft_strlen(input), input);
//     return(input);
// }

static int	token_count(const char *s, char *c, int i[2])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**token_fill(char **aux, const char *s, char *set, int i[2])
{
	int	n;
	int	len;
	int	q[2];

	n = 0;
	q[0] = 0;
	q[1] = 0;
	len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
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
			aux[i[2]++] = ft_substr(s, i[1], (i[0] - i[1]));
	}
	return (aux);
}

char	**init_split(const char *input, char *set)
{
	char	**aux;
	int		n;
	int		i[3];
	int		count[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	count[0] = 0;
	count[1] = 0;
	if (!input)
		return (NULL);
	n = token_count(input, set, count);
	if (n == -1)
		return (NULL);
	aux = malloc(sizeof(char *) * (n + 1));
	if (!aux)
		return (NULL);
	aux = token_fill(aux, input, set, i);
	aux[n] = NULL;
	return (aux);
}

/*
from parse.c
/// etype-padding + token_split * 
    init_split => split *str by space only (quote rule (ok if both))
    word_count + ft_fill_token ... ... seems legit!
    *** init_split: trunk at space to make node part
*/