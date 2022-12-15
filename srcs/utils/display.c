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
    printf("_[%s]_ \n", str);
}

void display_tkn(t_table *tab)
{
    t_token *token;
    int id;
    int i;

    id = 1;
    i = 0;

    token = tab->token; 
    if (!token)
        exit(0);
    // token->id = 1;
    // printf("TOKEN_NUM:[%d]", tab->tk_num); // how many tkn
    // printf("TOKEN_LEN:[%d]\n", token->tk_len); // tkn cmd / tkn
    while(id < tab->tk_num)
    {
        token->tk_len = ft_mx_len(tab->cmds[id]);
        i = 0;
        printf("token[%d]\n", id);
        while(++i < token->tk_len)
            mx_display_str(tab->cmds[id][i]);
        // tab->token++;
        id++;
    }
}
