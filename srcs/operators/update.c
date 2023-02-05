/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:11:13 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/14 23:22:29 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void update_output(char **out, int fd)
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
    ft_mx_free(&out);
    out = aux; 
}

void    execustom(char **out, char *full, char *args, char **envp) 
{
    pid_t   pid;
    int     fd[2];
    char    **mx; //token->cmd 

    // printf("welcome to execustom!\n");
    pipe(fd);                                             
    pid = fork();                                          
    if(!pid)
    {
        close(fd[READ_END]);
        mx = ft_split(args, ' ');
        // mx = ft_split(args, ' ');                                  
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

/*
        update_output   => building matrix info
        exec_custum     => framed outcome process
*/