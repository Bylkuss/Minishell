

#include "../../includes/minishell.h"

extern int g_status;

t_table *init_token(t_table *tab)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    
    tab->token = token;
    token->id = 0;
    token->cmd = NULL;  
    token->path = NULL;
    token->endtype = -1;
    token->infile = 0;
    token->outfile = 0;
    token->tk_len = 0;
    return (tab);   
}

t_table *init_tab(t_table *tab)
{
    tab->envp = NULL;
    tab->cmds = NULL;   
    tab->node = NULL;
    tab->tk_num = 0;
    tab->refs  = NULL;
    (void) tab->pid;
    tab->token = NULL;
    return (tab);
}

// /*
// main :  init_prompt => get user info to be stock into *p {struct t_dot}   
//         signal      => Global variable to be access anywhere ...
//                 getmypid    => fork process for multiple cmd.
//         init_vars   => split envp.args to stock into tab->envp 
//                 ms_setenv, ms_getenv   ==> signal.c      
//         getprompt   => prompt.c
//         check_args  => parse.c    
// */
