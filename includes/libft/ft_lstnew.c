/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:10:34 by loadjou           #+#    #+#             */
/*   Updated: 2022/04/20 13:19:18 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_content;

	new_content = NULL;
	new_content = malloc(sizeof(t_list));
	if (!new_content)
		return (NULL);
	new_content->next = NULL;
	new_content->content = content;
	return (new_content);
}
