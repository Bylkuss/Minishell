/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 06:21:03 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/05 10:46:36 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_minus(int *n, int *minus, int *tmp)
{
	if (*n == -2147483648)
	{
		*n = *n + 1;
		*minus = -1;
		*tmp = 1;
		*n = *n * -1;
	}
	else if (*n < 0)
	{
		*minus = -1;
		*n = *n * -1;
		*tmp = 0;
	}
	else if (*n >= 0)
	{
		*minus = 1;
		*tmp = 0;
	}
}

static int	ft_len(int nb)
{
	int	len;

	len = 0;
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	len++;
	return (len);
}

static void	ft_set_itoa(char *str, int len, int n, int tmp)
{
	while (n > 9)
	{
		str[len--] = (n % 10) + '0' + tmp;
		n = n / 10;
		tmp = 0;
	}
	str[len] = n + '0';
}

char	*ft_itoa(int n)
{
	char			*str;
	int				minus;
	int				len;
	int				tmp;

	ft_minus(&n, &minus, &tmp);
	len = ft_len(n);
	if (minus == -1)
	{
		str = malloc((len + 2) * sizeof(char));
		if (!str)
			return (NULL);
		len++;
		str[0] = '-';
	}
	else
	{
		str = malloc((len + 1) * sizeof(char));
		if (!str)
			return (NULL);
	}
	str[len--] = '\0';
	ft_set_itoa(str, len, n, tmp);
	return (str);
}
