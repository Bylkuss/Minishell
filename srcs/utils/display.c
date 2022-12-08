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
    printf(" :_:%s:_: \n", str);
}

void display_tkn(t_table *tab)
{
    t_token *token;
    
    token = tab->token; 
    if (!token)
        exit(0);
    token->id = 1;
    printf("TOKEN_NUM:\t%d\n", tab->tk_num); // how many tkn
    token->tk_len = fx_mx_len(tab->cmds[id])
    mx_display_tab(tab->cmds[id])
    // printf("\nCMD== %s ==  \t", tab->cmds[token->id]); // 
        // printf("ARG == %s == \t", tab->token->cmd[++id]);   
    // printf("END_TYPE == %d == \n", tab->token->endtype);   

}
