
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

static t_table *init_vars(t_table *tab, char *str, char **av)
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

static t_table *init_prompt(char **av, char **envp) 
{
        t_table *tab;      
        char *str;

        tab = malloc(sizeof(t_table ));
        init_tab(tab);
        str = NULL;
        tab->envp = ft_mx_dup(envp); //envp stk ref
        g_status = 0;
        getmypid(tab);                          
        tab = init_vars(tab, str, av);  //set envp. vars. frame
        return (tab); 
}

int main(int ac, char **av, char **envp) 
{
    char *str;
    char *input;
    // t_token token;
    t_table *tab;

    tab = init_prompt(av, envp);          //tab->envp , pid --> init_vars
    tab = init_token(tab);                // token frame
    while (av && ac) 
    {
        signal(SIGINT, handle_sigint);               
        signal(SIGQUIT, SIG_IGN);                    
        str = getprompt(tab);                
        if (str)
            input = readline(str);                    
        else
            input = readline("guest@minishell $ ");
        // 
            //fonction on his own { built_outs }
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
        /*
        */
        tab = check_args(input, tab);
        // mx_display_tab(tab->cmds);          //::    :://
            // break;
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