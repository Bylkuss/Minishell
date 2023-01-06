/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:11:13 by gehebert          #+#    #+#             */
/*   Updated: 2023/01/06 08:45:39 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//full_path maker 
char	*getcmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = path_join(*paths, "/");
		command = path_join(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

// char	*getpath(char *cmd, char **env)
    // {
    //     char	*path;
    //     char	*dir;
    //     char	*bin;
    //     int		i;

    //     i = 0;
    //     while (env[i] && str_ncmp(env[i], "PATH=", 5))
    //         i++;
    //     if (!env[i])
    //         return (cmd);
    //     path = env[i] + 5;
    //     while (path && str_ichr(path, ':') > -1)
    //     {
    //         dir = str_ndup(path, str_ichr(path, ':'));
    //         bin = path_join(dir, cmd);
    //         free(dir);
    //         if (access(bin, F_OK) == 0)
    //             return (bin);
    //         free(bin);
    //         path += str_ichr(path, ':') + 1;
    //     }
    //     return (cmd);
// }

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

/*
        update_output   => building matrix info
        exec_custum     => framed outcome process
*/