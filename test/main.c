
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"
#include "../libft/incs/libft.h"

int main(int ac, char **av, char **envp) 
    {
        char *str;
        char *input;
        t_dot p;

        // Configure readline to auto-complete paths when the tab key is hit.
        rl_bind_key('\t', rl_complete);
        
        str = av[0];
        p.envp = envp;
        while (ac)
        {
            // Display prompt and read input
            input = readline("prompt> ");

            // Check for EOF.
            if (!input)
                break;

            // Add input to readline history.
            add_history(input);
            // Do stuff...

            // Free buffer that was allocated by readline
            free(input);
        }
        if (!p.envp)
            printf("\n %s", str);
        return 0;
}

// static t_dot init_prompt(char **av, char **envp) 
// {
//     t_dot p;
//     char *str;

//     str = NULL;
//     p.cmds = NULL;
//     p.envp = ft_mx_dup(envp);                              
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