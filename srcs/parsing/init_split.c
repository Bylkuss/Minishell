/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:40:44 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/21 15:24:42 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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