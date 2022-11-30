#include "../../includes/minishell.h"



void mx_display_tab(char **tab)
{
    int i = 0;
    if (tab[i])// && tab[0])
    {
        while(tab[i++])
            printf ("%s :: \n", tab[i]);
        printf (" :: \n" );
    }
}

void mx_display_str(char *str)
{
    printf(" %s ++++  \n", str);
}

void display_tkn(t_table *tab)
{
    int id;

    id = 0;
    // t_token *token;
    // token = tab->token; 
    // if (!token)
    //     exit(0);
    printf("TOKEN_ID:\t%d\n", tab->tk_num); // how many tkn
    printf("\nCMD== %s ==  \t", tab->token->cmd[id]); // 
    if (tab->token->tk_len > 2 )
        printf("ARG == %s == \t", tab->token->cmd[++id]);   
    printf("END_TYPE == %d == \n", tab->token->endtype);   

}
