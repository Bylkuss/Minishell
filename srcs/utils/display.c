#include "../../includes/minishell.h"



void mx_display_tab(char **tab)
{
    int i = 0;

        printf("START:");
        while(tab && (*tab[i] != '\0'))
        {
            printf ("(%s),", tab[i]);
            i++;
        }
        printf(":END\n");
}

void mx_display_str(char *str)
{
    printf(" \n{%s}\n ", str);
}

// void display_tkn(t_table *tab)
    // {
    //     t_node *node;
    //     int id;
    //     int i;
    //     int etype;
    //     int tk_len;

    //     id = 1;
    //     i = 0;
    //     node = tab->node; 
    //     if (!node)
    //         exit(0);
        
    //     // node->endtype = 0;
    //     while (id <= tab->tk_num)
    //     {
    //         tk_len = ft_mx_len(tab->cmds[id]);
    //         printf("node->id:[%d/%d]:: {", id, tab->tk_num);
    //         // printf("node->tk_len   :[%d]\n", node->tk_len);
    //         i = -1;
    //         while(++i < tk_len)
    //         {
    //             mx_display_str(tab->cmds[id][i]);
    //         }
    //         // printf(":: endtype:[%s]", tab->cmds[id][tk_len - 1]);
    //         etype = set_endtype(tab, tab->cmds[id][tk_len - 1]);
    //         printf("} :: etype:[%d]\n", etype);
    //         id++;
    //     }
// }

void display_one_tkn(t_node *node, int id)
{
    // t_node *node;
    // int id;
    int i;
    int etype;
    int tk_len;

    // id = 1;
    i = 0;
    // node = tab->node; 
    if (!node)
        exit(0);
    
    // node->endtype = 0;
    if (node->id)
    {
        tk_len = ft_mx_len(node->cmd);
        printf("ONLY_ONE:: node->id:[%d]:: {", id);
        printf("node->tk_len   :[%d]\n", node->tk_len);
        i = -1;
        while(++i < tk_len)
        {
            mx_display_str(node->cmd[i]);
        }
        // printf(":: endtype:[%s]", tab->cmds[id][tk_len - 1]);
        // etype = set_endtype(tab, tab->cmds[id][tk_len - 1]);
        printf("}::t->i:[%d]::", node->infile);
        printf("t->o[%d]::\n", node->outfile);
        // id++;
    }
}

// void display_tkn_id(t_node *t, int id)
    // {

    //     int i;
    //     int etype;
    //     int tk_len;

    //     i = 0;
    //     if (!t)
    //         exit(0);
        
    //     // node->endtype = 0;
    //     // while (id <= tab->tk_num)
    //     // {
    //         tk_len = ft_mx_len(t->cmd[id]);
    //         printf("node->id:[%d]:: {", id);
    //         // printf("node->tk_len   :[%d]\n", node->tk_len);
    //         i = -1;
    //         while(++i < tk_len)
    //         {
    //             mx_display_str(t->cmd[id][i]);
    //         }
    //         // printf(":: endtype:[%s]", tab->cmds[id][tk_len - 1]);
    //         // etype = set_endtype(tab, t->cmd[id][z- 1]);
    //         printf("} :: etype:[%d]\n", t->endtype);
    //         id++;
    //     // }
// }