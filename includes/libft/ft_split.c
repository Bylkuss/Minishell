/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 09:17:54 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/23 16:49:43 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			words++;
		i++;
	}
	return (words);
}

static char	*splitstr(const char *s, char c, int *start)
{
	int		i;
	char	*str;
	int		j;

	j = *start;
	i = 0;
	while (s[j] == c)
		j++;
	while (s[j] && s[j] != c)
	{
		j++;
		i++;
	}
	str = ft_substr(s, j - i, i);
	*start = j;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		words;

	if (!s)
		return (NULL);
	i = 0;
	words = count_word(s, c);
	strs = ft_calloc(sizeof(char *), words + 1);
	if (!strs)
		return (NULL);
	j = 0;
	while (i < words)
	{
		strs[i] = splitstr(s, c, &j);
		i++;
	}
	return (strs);
}
/*
int	main(void)
{
	char	c;
	char	*str;
	char	**tab;
	int		i;
	int		word;

	i = 0;
	c = '/';
	// str = "/abcde///12345/fghsfths/sfgnsfdhj/dyjdyjs////stjhsfthsr///srthsfgh/";
	str = ""  tripouille  42  ", ' '";
	word = count_word(str, c);
	tab = ft_split(str, c);
	while (i < word)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
*/