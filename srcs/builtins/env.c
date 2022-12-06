/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:12:07 by bylkus            #+#    #+#             */
/*   Updated: 2022/11/29 16:31:53 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_strcmp_u(char *s1, char *s2, char until)
{
    int i = 0;
    while(s1[i] && s2[i] && s1[i] != until)
        i++;
    return s1[i] - s2[i];
}

void    env(char **envp)
{
    int i = 0;
    while(envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
}

static void edit_env(char **envp, int pos)
{
    while(*envp && envp[pos + 1])
    {
        envp[pos] = envp[pos + 1];
        pos++;
    }
}

void    unset(char **cmd, char **envp)
{
    int i = 0;
    if(!cmd[1])
    {
        printf("Missmatch args nb\n");
        return;
    }
    while(envp[i])
    {
        if(!ft_strcmp_u(envp[i], cmd[1], '='))
        {
            printf("VAR to unset: [%d] %s\n\n", i, envp[i]);
            if(!envp[i + 1])
                free(envp[i]);
            edit_env(envp, i);
        }
        i++;
    }
    free(envp[i]);
}

static int check_export_cmd(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(i > 0 && str[i] == '=')
            return 1;
        i++;
    }
    return 0;
}


void    export(char **cmd, char **envp)
{
    if(cmd[1] && check_export_cmd(cmd[1]))
    {
        envp = ft_calloc(sizeof(char *), 1);
        envp[ft_arraylen(envp) - 1] = ft_strdup(cmd[1]);
        envp[ft_arraylen(envp)] = NULL;
    }
    else
        printf("%s not found\n", cmd[1]);
}

