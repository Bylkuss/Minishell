/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:29 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/25 15:15:41 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char **cmd)
{
	int		args;
	char	*str;
	int		i;
    int flag = 0;
    
	args = 0;
	i = 1;
	while (cmd[args])
		args++;
	if (args > 1)
	{
		while (cmd[i])
		{
            if(ft_strcmp(cmd[i], "-n") == 0)
            {
                flag = 1;    
                i++;
            }
			// if (!str)
			// 	str = ft_strdup(cmd[i]);
			// else
				str = ft_strjoin(str, cmd[i]);
			free(cmd[i]);
			i++;
		}
        printf("%s\n", str);
        if(is_quoted(str))
        {
            // print_skip_qt(str);
            printf("\n");
        }
        else
            printf("Error dquote\n");
	}
	else
	{
		printf("Error Wrong args\n");
	}
}
