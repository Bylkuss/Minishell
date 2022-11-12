/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:48:49 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/11 02:08:37 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/minishell.h"
# include "../libft/incs/libft.h"

extern int g_status;



// static void update_output(char **mx, int fd) {
    //     char **aux;
    //     char *tmp;
    //     char *line;

    //     aux = NULL;
    //     line = NULL;
    //     while(1)
    //     {
    //         line = get_next_line(fd);                      
    //         if(!line)
    //             break;
    //         tmp = ft_strtrim(line, "\n");                       
    //         free(line);
    //         aux = ft_mx_ext(aux, tmp);                       
    //         free(tmp);
    //     }
    //     ft_mx_free(*mx);
    //     *mx = aux; 
// }

// void    exec_custom(char **out, char *full, char *args, char **envp) 
    // {
    //     pid_t   pid;
    //     int     fd[2];
    //     char    **mx;

    //     pipe(fd);                                             
    //     pid = fork();                                          
    //     if(!pid)
    //     {
    //         close(fd[READ_END]);
    //         mx = ft_split(args, ' ');                          
    //         dup2(fd[WRITE_END], STDOUT_FILENO);
    //         close(fd[WRITE_END]);
    //         if(!access(full, F_OK))
    //             execve(full, mx, envp);
    //         exit(1);
    //     }
    //     close(fd[WRITE_END]);
    //     waitpid(pid, NULL, 0);
    //     // update_output(out, fd[READ_END]);                      
    //     close(fd[READ_END]); 
// }

static char **split_all(char **args, t_dot p)
{
    char **subsplit;
    int i;
    // int quotes[2];

    (void) p;
    i = -1;
    while (args && args[++i])
    {
        // args[i] = expand_vars(args[i], -1, quotes, p);       
        // args[i] = expand_path(args[i], -1, quotes, \
        //     mini_getenv("HOME", prompt->envp, 4));              
        subsplit = ft_cmdsubsplit(args[i], "<|>");              
        ft_mx_rpl(&args, subsplit, i);                           
        i += ft_mx_len(subsplit) - 1;                          
        ft_mx_free(&subsplit);                                 
    }
    return (args); 
}

static t_dot parse_args(char **args, t_dot p)
{
    t_mini m;
    int is_exit;
    int i;

    is_exit = 0;
    m.full_cmd  = split_all(args, p);              
    if (!m.full_cmd)
        return (p);
    // i = ft_lstsize(m.full_cmd);
    // g_status = builtin(p, p->cmds, &is_exit, 0);             
    i = 0;
    while (i-- > 0)
        waitpid(-1, &g_status, 0);
    // if (!is_exit && &g_status == 13)
    //     g_status = 0;
    if (g_status > 255)
        g_status = g_status / 255;
    // if (args && is_exit)
    // {
    //     ft_lstclear(&p->cmds, free_content);
    //     return (NULL);
    // }
    return (p);
}

t_dot check_args(char *out, t_dot p) 
{
    char    **a;
    t_mini  m;

    if (!out)
    {
        printf("exit\n");
        return (p);
    }
    if (out[0] != '\0')
        add_history(out);                                 
    m.full_cmd = ft_cmdtrim(out, " ");                               
    free(out);
    // if (!a)
    //     return ("");
    p = parse_args(m.full_cmd, p);                                    
    // if (p && p->cmds)
        // n = p->cmds->content;
    // if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
        // p->envp = mini_setenv("_", n->full_cmd[ft_mx_len(n->full_cmd) - 1], p->envp, 1);                                         --
    // if (p && p->cmds)
    //     ft_lstclear(&p->cmds, free_content);
    return (p); 
}

