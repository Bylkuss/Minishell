/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:56:07 by bylkus            #+#    #+#             */
/*   Updated: 2022/11/25 14:05:23 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quoted(char *str)
{
	int	i;
	int	s_qt;
	int	d_qt;

	i = 0;
	s_qt = 0;
	d_qt = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_qt++;
		else if (str[i] == '\'')
			s_qt++;
		i++;
	}
	if (d_qt % 2 == 0 || s_qt % 2 == 0)
		return (1);
	return (0);
}

void	print_skip_qt(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i++;
		write(1, &s[i], 1);
		i++;
	}
}
