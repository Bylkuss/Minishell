/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapi_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:56:31 by loadjou           #+#    #+#             */
/*   Updated: 2023/03/14 23:56:36 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	mapi_f(unsigned int i, char str)
{
	printf("test fonction: index = %d and %c\n", i, str);
	return (str - 32);
}
