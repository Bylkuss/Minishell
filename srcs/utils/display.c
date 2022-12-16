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
    printf("_[%s]", str);
}

void display_tkn(t_table *tab)
{
    t_token *token;
    int id;
    int i;
    int etype;
    int tk_len;

    id = 1;
    i = 0;
    token = tab->token; 
    if (!token)
        exit(0);
    
    // token->endtype = 0;
    while (id <= tab->tk_num)
    {
        tk_len = ft_mx_len(tab->cmds[id]);
        printf("\ntoken->id:[%d]::", id);
        // printf("token->tk_len   :[%d]\n", token->tk_len-1);
        i = 0;
        while(++i < tk_len)
        {
            mx_display_str(tab->cmds[id][i]);
        }
        printf("_:: endtype:[%s]", tab->cmds[id][tk_len - 1]);
        etype = set_endtype(tab, tab->cmds[id][tk_len - 1]);
        printf("_:: etype:[%d]\n", etype);
        id++;
    }
}
