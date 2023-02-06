/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:19:19 by gehebert          #+#    #+#             */
/*   Updated: 2023/02/02 11:07:08 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid nuber of argument\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"

typedef struct s_pipex
{
    pid_t   pid1;
    pid_t   pid2;
    int     tube[2];
    int     infile;
    int     outfile;
    char    *paths;
    char    **cmd_paths;
    char    **cmd_args;
    char    *cmd;
}   t_pipex;



char	*path_join(char *path, char *bin);
int		str_ncmp(char *str1, char *str2, int n);
int		str_ichr(char *str, char c);
char	*str_ndup(char *str, unsigned int n);
char	**str_split(char *str, char sep);


void    parent_free(t_pipex *pipex);
void    child_free(t_pipex *pipex);
void    first_child(t_pipex pipex, char **av, char **envp);
void    second_child(t_pipex pipex, char **av, char **envp);
void    close_pipe(t_pipex *pipex);
char    *getcmd(char **paths, char *cmd);
/************************************************/
// int     execute_cmd(t_table *tab, t_token *tok);
    
#endif
