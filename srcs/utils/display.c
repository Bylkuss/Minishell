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
    // t_token *token;
    // token = tab->token; 
    // if (!token)
    //     exit(0);
    printf("TOKEN_ID:\t%d\n", tab->tkn_num); // how many tkn
    printf("\nCMD== %s ==  \t", tab->token->cmd); // 
    if (tab->token->tkn_len > 2 )
        printf("ARG == %s == \t", tab->token->attr);   
    printf("END_TYPE == %d == \n", tab->token->endtype);   

}
