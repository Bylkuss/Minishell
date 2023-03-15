/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:55:43 by loadjou           #+#    #+#             */
/*   Updated: 2023/03/15 10:55:43 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static int	ft_count_words(const char *str, char charset)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != charset)
		{
			words++;
			while (str[i] != charset && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	**ft_write_split(char **split, const char *str, char charset)
{
	size_t	i;
	size_t	j;
	int		word;
	size_t	len;

	word = 0;
	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		while (str[i] == charset || str[i] == '\0')
			i++;
		j = i;
		while (str[i] != charset && str[i] != '\0')
			i++;
		if (j >= len)
			split[word++] = "\0";
		else
			split[word++] = ft_substr(str, j, i - j);
	}
	return (split);
}

char	**ft_split(const char *str, char c)
{
	char	**res;
	int		words;

	if (!str)
		return (NULL);
	words = ft_count_words(str, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (res == NULL)
		return (NULL);
	res = ft_write_split(res, str, c);
	res[words] = NULL;
	return (res);
}
