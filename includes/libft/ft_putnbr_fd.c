/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:19:17 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/20 13:16:46 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n <= 9 && n >= 0)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else if (n < 0)
	{
		if (n <= -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			write(fd, "-", 1);
			n /= -1;
			ft_putnbr_fd(n, fd);
		}
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
