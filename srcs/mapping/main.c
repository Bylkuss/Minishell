
#include "../../includes/minishell.h"

extern int g_status;

    static void getmypid(t_table *tab) 
    {
        pid_t   pid;

        pid = fork();                                             
        if (pid < 0)
        {
            //mini_perror(FORKERR, NULL, 1);                        
            ft_mx_free(&tab->envp);                              
            exit(1);
        }
        if (!pid)
        {
        ft_mx_free(&tab->envp);                                  
            exit(1);
        }
        waitpid(pid, NULL, 0);                                    
        tab->pid = pid - 1; 
    }

static t_token *init_token(t_table tab)
{
        t_token *token;
        token = table->token;
        token->cmd = NULL;  
        token->arg = NULL;  
        token->table = NULL;
        token->endtype = DEAD_END;
        return (token);   
}

static t_table init_vars(t_table tab, char *str, char **av)
{
        char *num;

        str = getcwd(NULL, 0);                                            
        tab->envp = ms_setenv("PWD", str, tab->envp, 3);         
        free(str);
        str = ms_getenv("SHLVL", tab->envp, 5);                     
        if (!str || ft_atoi(str) <= 0)
            num = ft_strdup("1");
        else
            num = ft_itoa(ps_atoi(str) + 1);
        free(str);
        tab->envp = ms_setenv("SHLVL", num, tab->envp, 5);      
        free(num);
        str = ms_getenv("PATH", tab->envp, 4);                      
        if(!str)
            tab->envp = ms_setenv("PATH", "/usr/local/sbin/:/usr/local/bin:/usr/bin:/bin", tab->envp, 4);  //
        free(str);
        str = ms_getenv("_", tab->envp, 1);                          
        if (!str)
            tab->envp = ms_setenv("_", av[0], tab->envp, 1);         
        free(str);
            return (tab); 
}

static t_table init_prompt(char **av, char **envp) 
{
        t_table tab;
        
        char *str;

        str = NULL;
        tab->envp = ft_mx_dup(envp); 
        tab->token = malloc(t_token);
        g_status = 0;
        getmypid(&tab);                          
        tab = init_vars(tab, str, av);            
        return (tab); 
}

int main(int ac, char **av, char **envp) 
{
    char *str;
    char *input;
    t_token *token;
    t_table tab;

    tab = init_prompt(av, envp);      
    init_token(tab);
    while (av && ac) 
    {
        signal(SIGINT, handle_sigint);               
        signal(SIGQUIT, SIG_IGN);                    
        str = getprompt(p);                
        if (str)
            input = readline(str);                    
        else
            input = readline("guest@minishell $ ");
            // 
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
            // 
        free(str);
        if (!check_args(input, &p))
            break;
        // else 
        //     mx_display_tkn(token); 

    }
    exit(g_status); 
}


/*
main :  init_prompt => get user info to be stock into *p {struct t_dot}   
        signal      => Global variable to be access anywhere ...
                getmypid    => fork process for multiple cmd.
        init_vars   => split envp.args to stock into tab->envp 
                ms_setenv, ms_getenv   ==> signal.c      
        getprompt   => prompt.c
        check_args  => parse.c    
*/


// #include <stdlib.h>
    // #include <stdio.h>
    // #include <readline/readline.h>
    // #include <readline/history.h>
    // #include "../../includes/minishell.h"
    // #include "../libft/incs/libft.h"

    // int main(int ac, char **av, char **envp) 
    //     {
    //         char *str;
    //         char *input;
    //         t_dot p;

    //         // Configure readline to auto-complete paths when the tab key is hit.
    //         rl_bind_key('\t', rl_complete);
            
    //         str = av[0];
    //         tab->envp = envp;
    //         while (ac)
    //         {
    //             // Display prompt and read input
    //             input = readline("prompt> ");

    //             // Check for EOF.
    //             if (!input)
    //                 break;

    //             // Add input to readline history.
    //             add_history(input);
    //             // Do stuff...

    //             // Free buffer that was allocated by readline
    //             free(input);
    //         }
    //         if (!tab->envp)
    //             printf("\n %s", str);
    //         return 0;
    // }

// static t_dot init_prompt(char **av, char **envp) 
    // {
    //     t_dot p;
    //     char *str;
    //     str = NULL;
    //     p.cmds = NULL;
    //     tab->envp = ft_mx_dup(envp);                              
    //     // g_status = 0;
    //     mini_getpid(&p);                          
    //     p = init_vars(p, str, av);            
    //     return (p); 
    // }
    // int main(int ac, char **av, char **envp) 
    // {
    //     char *str;
    //     char *input;
    //     t_dot p;
    //     p = init_prompt(av, envp);                   
    //     while (av && ac) {
    //         signal(SIGINT, handle_sigint);               
    //         signal(SIGQUIT, SIG_IGN);                    
    //         str = mini_getprompt(p);                
    //         if (str)
    //             input = readline(str);                    
    //         else
    //             input = readline("guest@minishell $ ");     
    //         free(str);
    //         if (!check_args(input, &p))             
    //             break;
    //     }
    //     exit(g_status); 
    // }