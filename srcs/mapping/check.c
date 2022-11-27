/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:59:09 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/25 15:07:44 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

static void getmypid(t_dot *p) 
{
    pid_t   pid;

    pid = fork();                                             
    if (pid < 0)
    {
        //mini_perror(FORKERR, NULL, 1);                        
        ft_mx_free(&p->envp);                              
        exit(1);
    }
    if (!pid)
    {
       ft_mx_free(&p->envp);                                  
        exit(1);
    }
    waitpid(pid, NULL, 0);                                    
    p->pid = pid - 1; 
}

static t_dot init_vars(t_dot p, char *str, char **av)
{
    char *num;
    // t_mini m;

    str = getcwd(NULL, 0);
    p.envp = ms_setenv("PWD", str, p.envp, 3);          // 
    free(str);
    str = ms_getenv("SHLVL", p.envp, 5);                       ///
    if (!str || ft_atoi(str) <= 0)
        num = ft_strdup("1");
    else
        num = ft_itoa(ps_atoi(str) + 1);
    free(str);
    p.envp = ms_setenv("SHLVL", num, p.envp, 5);       //
    free(num);
    str = ms_getenv("PATH", p.envp, 4);                       ///
    if(!str)
        p.envp = ms_setenv("PATH", "/usr/local/sbin/:/usr/local/bin:/usr/bin:/bin", p.envp, 4);  //
    free(str);
    str = ms_getenv("_", p.envp, 1);                          ///
    if (!str)
        p.envp = ms_setenv("_", av[0], p.envp, 1);         //
    free(str);
        return (p); 
}

t_dot init_prompt(char **av, char **envp) 
{
    t_dot p;
    // t_mini m;
    char *str;

    str = NULL;
    p.cmds = NULL;
    p.envp = ft_mx_dup(envp);                              
    g_status = 0;
    getmypid(&p);                          
    p = init_vars(p, str, av);            
    return (p); 
}

int main(int ac, char **av, char **envp) 
{
    char *str;
    char *input;
    // char **test_cd = NULL;
    t_dot p;

    p = init_prompt(av, envp);      // 
    // mx_display_tab(p.envp);
    while (av && ac) 
    {
        signal(SIGINT, handle_sigint);               
        signal(SIGQUIT, SIG_IGN);                    
        str = getprompt(p); 
        str = NULL;               
        if (str)
            input = readline(str);                    
        else
            input = readline("Minishell $ ");
        if(ft_strcmp(input, "exit") == 0)
            exit(0);
        if (ft_strlen(input) > 0)
            add_history(input);
        if(ft_strnstr(input, "cd", 10))
            cd(ft_split(input, ' '), envp);
        else if (ft_strnstr(input, "pwd", 10))
            pwd();
        else if(ft_strnstr(input, "echo", 10))
            echo(ft_split(input, ' '));
        else if (ft_strnstr(input, "ls", 5))
            execve("/usr/bin/ls", ft_split(input, ' '), envp);
        free(str);
        if (!check_args(input, &p))
            break;
    }
    exit(g_status); 
}


/*
main :  init_prompt => get user info to be stock into *p {struct t_dot}   
        signal      => Global variable to be access anywhere ...
                getmypid    => fork process for multiple cmd.
        init_vars   => split envp.args to stock into p.envp 
                ms_setenv, ms_getenv   ==> signal.c      
        getprompt   => prompt.c
        check_args  => parse.c    
*/
