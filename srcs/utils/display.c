#include "../../includes/minishell.h"



void mx_display_tab(char **tab)
{
    int i = -1;
    if (tab)// && tab)
    {
        while(*tab[++i])
            printf ("%s :: ", tab[i]);
        printf (" :: \n" );
    }
}

void mx_display_str(char *str)
{
    printf(" %s ++++  \n", str);
}

void display_tkn(t_table *tab)
{
    t_token *token;
    int id;

    id = 0;
    token = tab->token; 
    if (!token)
        exit(0);
    printf("TOKEN_ID:\t%d\n", tab->token_len); // how many tkn
    printf("\nCMD== %s ==  \t", tab->token->cmd[id]); // 
    while (tab->token->cmd_len > 2 && id++ < tab->token->cmd_len)
        printf("ARG == %s == \t", tab->token->cmd[id]);   
    printf("END_TYPE == %d == \n", tab->token->endtype);   

}
