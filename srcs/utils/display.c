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
    //     t_token *token;
    //     int id;
    //     int i;
    //     int etype;
    //     int tk_len;

    //     id = 1;
    //     i = 0;
    //     token = tab->token; 
    //     if (!token)
    //         exit(0);
        
    //     // token->endtype = 0;
    //     while (id <= tab->tk_num)
    //     {
    //         tk_len = ft_mx_len(tab->cmds[id]);
    //         printf("token->id:[%d/%d]:: {", id, tab->tk_num);
    //         // printf("token->tk_len   :[%d]\n", token->tk_len);
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

// void display_one_tkn(t_token *token, int id)
// {
//     // t_token *token;
//     // int id;
//     int i;
//     int etype;
//     int tk_len;

//     // id = 1;
//     i = 0;
//     // token = tab->token; 
//     if (!token)
//         exit(0);
    
//     // token->endtype = 0;
//     if (token->id)
//     {
//         tk_len = ft_mx_len(token->cmd[id]);
//         printf("ONLY_ONE:: token->id:[%d]:: {", id);
//         // printf("token->tk_len   :[%d]\n", token->tk_len);
//         i = -1;
//         while(++i < tk_len)
//         {
//             mx_display_str(token->cmd[id][i]);
//         }
//         // printf(":: endtype:[%s]", tab->cmds[id][tk_len - 1]);
//         // etype = set_endtype(tab, tab->cmds[id][tk_len - 1]);
//         printf("}::t->i:[%d]::", token->infile);
//         printf("t->o[%d]::\n", token->outfile);
//         // id++;
//     }
// }

// void display_tkn_id(t_token *t, int id)
// {

//     int i;
//     int etype;
//     int tk_len;

//     i = 0;
//     if (!t)
//         exit(0);
    
//     // token->endtype = 0;
//     // while (id <= tab->tk_num)
//     // {
//         tk_len = ft_mx_len(t->cmd[id]);
//         printf("token->id:[%d]:: {", id);
//         // printf("token->tk_len   :[%d]\n", token->tk_len);
//         i = -1;
//         while(++i < tk_len)
//         {
//             mx_display_str(t->cmd[id][i]);
//         }
//         // printf(":: endtype:[%s]", tab->cmds[id][tk_len - 1]);
//         // etype = set_endtype(tab, t->cmd[id][tk_len - 1]);
//         printf("} :: etype:[%d]\n", t->endtype);
//         id++;
//     // }
// }