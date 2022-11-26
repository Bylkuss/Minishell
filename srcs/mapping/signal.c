/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:40:01 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/23 20:04:53 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int g_status;

void    handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        g_status = 130;
        ioctl(STDIN_FILENO, TIOCSTI, "\n");                           
        // rl_replace_line("", 0);                                    
        rl_on_new_line();                                          
    } 
}

char    *ms_getenv(char *var, char **envp, int n)
{
    int i;
    int n2;

    i = 0;
    if (n < 0)
        n = ft_strlen(var);
    while (!ft_strchr(var, '-') && envp && envp[i])
    {
        n2 = n;
        if (n2 < ft_strchr_i(envp[i], '='))                         
            n2 = ft_strchr_i(envp[i], '=');                          
        if(!ft_strncmp(envp[i], var, n2))
            return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
        i++;
    }
    return (NULL);  
}
 
char    **ms_setenv(char *var, char *value, char **envp, int n)
{
    int i[2];
    char *aux[2];

    if (n < 0)
        n = ft_strlen(var);
    i[0] = -1;
    aux[0] = ft_strjoin(var, "=");
    aux[1] = ft_strjoin(aux[0], value);
    free(aux[0]);
    while (!ft_strchr(var, '=') && envp && envp[++i[0]])
    {
        i[1] = n;
        if (i[1] < ft_strchr_i(envp[i[0]], '='))                     
            i[1] = ft_strchr_i(envp[i[0]], '=');                     
        if (!ft_strncmp(envp[i[0]], var, i[1]))
        {
            aux[0] = envp[i[0]];
            envp[i[0]] = aux[1];
            free(aux[0]);
            return (envp);
        }
    }
    envp = ft_mx_ext(envp, aux[1]);                                 
    free(aux[1]);
    return (envp); 
}
/*
from main.c
    handle_signal   => signal reference (iotcl) fd, files, err
    ms_setenv       => fix data into struct     
    ms_getenv       => go get data to bet set      
*/