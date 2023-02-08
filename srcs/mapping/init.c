

#include "../../includes/minishell.h"

extern int g_status;

t_table *init_node(t_table *tab)
{
    t_node *node;

    node = malloc(sizeof(t_node));
    tab->node = node;
    node->id = 0;
    node->cmd = NULL;  
    node->path = NULL;
    node->xfile = NULL;
    node->etype = -1;
    node->infile = 0;
    node->outfile = 1;
    node->nod_len = 0;
    return (tab);   
}

t_table *init_tab(t_table *tab)
{
    tab->envp = NULL;
    tab->cmds = NULL ;   
    tab->token = NULL;
    tab->refs  = NULL;
    tab->nod_num = 1;
    (void) tab->pid;
    return (tab);
    // tab->node = NULL;
}

t_table 	*node_alloc(t_table *tab)	/* call by parse_  <<(node_ized)	*/
{
	int i;
	int id;			// token_id
	int node_len;		// array width

	id = 1; 
	i = 0;
	node_len = tab->refs[tab->num];	
        // printf("DEBUG : start_dup:nod_len(%d)::\n", nod_len);	
        // printf("DEBUG : start_dup:nod_num(%d)::\n", tab->nod_num);
	tab->cmds = (char ***)malloc(sizeof(char **) * node_len);
 	while( ++i <= tab->num)
	{
		nod_len = (tab->refs[id] - nod_len);
		while( id <= nod_len)
		{
			tab->cmds[id] = (char **)malloc(sizeof(char *) * nod_len);
			id++;
		}
	}			
	return (tab);
}

			// tab->node->cmd[id] = (char **)malloc(sizeof(char *) * nod_len);

// /*
// main :  init_prompt => get user info to be stock into *p {struct t_dot}   
//         signal      => Global variable to be access anywhere ...
//                 getmypid    => fork process for multiple cmd.
//         init_vars   => split envp.args to stock into tab->envp 
//                 ms_setenv, ms_getenv   ==> signal.c      
//         getprompt   => prompt.c
//         check_args  => parse.c    
// */
