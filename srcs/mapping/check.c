/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:59:09 by gehebert          #+#    #+#             */
/*   Updated: 2022/11/17 14:15:42 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

// extern int g_status;

// t_table *init_token(t_table *tab)       // call by main
// {
//         t_token *token;

//         token = malloc(sizeof(t_token));
//         token->id = 0;
//         token->cmd = NULL;  
//         token->path = NULL;
//         token->endtype = DEAD_END;
//         token->infile = 0;
//         token->outfile = 0;
//         token->tk_len = 0;
//         token->table = tab;
//         return (tab);   
// }

// t_table *init_tab(t_table *tab)
// {
        
//         tab->envp = NULL;
//         tab->cmds = NULL;
//         tab->node = NULL;
//         tab->tk_num = 0;
//         (void) tab->pid;
//         tab->token = NULL;
//         return (tab);
// }


// t_table  *check_args(char *out, t_table tab)  // maybe needed to return (tab)
// {
//     char    **arr;
//     if (!out)
//     {
//         printf("exit\n");
//         return (NULL);
//     }
//     if (out[0] != '\0')
//         add_history(out);
//     //
//     tab->cmds = space_split(out, " ");  
//                 //input divided by space  **tab    
//                 // if (tab)
//                 //     mx_display_tab(tab->cmds);
//     // free(out);
//     if (!tab)
//         return ("");
//     // tab->token  ... 
//     tab->token = parse_args(tab);    
//     if (tab && tab->token)
//         tab->attr = ;
//     /*
//        token need to be ID _cmd, _attr, _end   
//     */
//     if (tab && tab->cmds && tab->token && tab->tk_num > 0)
//     {
//         // display_tkn(token);
//         mx_display_tab(tab->cmds);
//         /*
//         // p->envp = ms_setenv("_", m->full_cmd[ft_mx_len(m->full_cmd)
//         //  - 1], p->envp, 1);                                        
//             //     ft_lstclear(&p->cmds, free_content);
//             */
//     }
//     return (tab); 
// }

/*
// static void getmypid(t_dot *p) 
// {
//     pid_t   pid;
//     pid = fork();                                             
//     if (pid < 0)
//     {
//         //mini_perror(FORKERR, NULL, 1);                        
//         ft_mx_free(&p->envp);                              
//         exit(1);
//     }
//     if (!pid)
//     {
//        ft_mx_free(&p->envp);                                  
//         exit(1);
//     }
//     waitpid(pid, NULL, 0);                                    
//     p->pid = pid - 1; 
// }
// static t_token *init_token(t_dot *p)
// {
//     t_token *token = NULL;
//     token->table = p->envp;
//     token->cmd = NULL;  //p->cmds;//>content;
//     token->arg = NULL;  //p->cmds->next->content;
//     token->endtype = DEAD_END;
//     return (token);   
// }
// static t_dot init_vars(t_dot p, char *str, char **av)
// {
//     char *num;
//     str = getcwd(NULL, 0);                                            
//     tab->envp = ms_setenv("PWD", str, tab->envp, 3);          // 
//     free(str);
//     str = ms_getenv("SHLVL", tab->envp, 5);                       ///
//     if (!str || ft_atoi(str) <= 0)
//         num = ft_strdup("1");
//     else
//         num = ft_itoa(ps_atoi(str) + 1);
//     free(str);
//     tab->envp = ms_setenv("SHLVL", num, tab->envp, 5);       //
//     free(num);
//     str = ms_getenv("PATH", tab->envp, 4);                       ///
//     if(!str)
//         tab->envp = ms_setenv("PATH", "/usr/local/sbin/:/usr/local/bin:/usr/bin:/bin", tab->envp, 4);  //
//     free(str);
//     str = ms_getenv("_", tab->envp, 1);                          ///
//     if (!str)
//         tab->envp = ms_setenv("_", av[0], tab->envp, 1);         //
//     free(str);
//         return (p); 
// }
// static t_dot init_prompt(char **av, char **envp) 
// {
//     t_dot p;
//     char *str;
//     str = NULL;
//     p.cmds = NULL;
//     tab->envp = ft_mx_dup(envp); 
//     p.token = malloc(t_token);
//     g_status = 0;
//     getmypid(&p);                          
//     p = init_vars(p, str, av);            
//     return (p); 
// }
// int main(int ac, char **av, char **envp) 
// {
//     char *str;
//     char *input;
//     t_token *token;
//     // char **test_cd = NULL;
//     t_dot p;
//     p = init_prompt(av, envp);      // 
//     init_token(p);
//     // mx_display_tab(tab->envp);
//     while (av && ac) 
//     {
//         signal(SIGINT, handle_sigint);               
//         signal(SIGQUIT, SIG_IGN);                    
//         str = getprompt(p);                
//         if (str)
//             input = readline(str);                    
//         else
//             input = readline("guest@minishell $ ");
//         if(ft_strcmp(input, "exit") == 0)
//             exit(0);
//         if (ft_strlen(input) > 0)
//             add_history(input);
//         if(ft_strnstr(input, "cd", 10))
//             cd(ft_split(input, ' '), envp);
//         else if (ft_strnstr(input, "pwd", 10))
//             pwd();
//         else if(ft_strnstr(input, "echo", 10))
//             echo(ft_split(input, ' '));
//         free(str);
//         if (!check_args(input, &p))
//             break;
//         // else 
//         //     mx_display_tkn(token); 

//     }
//     exit(g_status); 
// }
*/

// /*
// main :  init_prompt => get user info to be stock into *p {struct t_dot}   
//         signal      => Global variable to be access anywhere ...
//                 getmypid    => fork process for multiple cmd.
//         init_vars   => split envp.args to stock into tab->envp 
//                 ms_setenv, ms_getenv   ==> signal.c      
//         getprompt   => prompt.c
//         check_args  => parse.c    
// */
