/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:11:13 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/17 13:36:50 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void update_output(char ***mx, int fd)
{
    char **aux;
    char *tmp;
    char *line;

    aux = NULL;
    line = NULL;
    while(1)
    {
        line = get_next_line(fd);                      
        if(!line)
            break;
        tmp = ft_strtrim(line, "\n");                       
        free(line);
        aux = ft_mx_ext(aux, tmp);                       
        free(tmp);
    }
    // ft_mx_free(mx);
    *mx = aux; 
}

void    exec_custom(char ***out, char *full, char *args, char **envp) 
{
    pid_t   pid;
    int     fd[2];
    char    **mx;

    pipe(fd);                                             
    pid = fork();                                          
    if(!pid)
    {
        close(fd[READ_END]);
        mx = ft_split(args, ' ');                          
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]);
        if(!access(full, F_OK))
            execve(full, mx, envp);
        exit(1);
    }
    close(fd[WRITE_END]);
    waitpid(pid, NULL, 0);
    update_output(out, fd[READ_END]);                      
    close(fd[READ_END]); 
}
