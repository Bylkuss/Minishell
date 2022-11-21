#include "../../includes/minishell.h"



void mx_display_tab(char **tab)
{
    int i = -1;
    if (tab[i])// && tab[0])
    {
        while(*tab[++i])
            printf ("%s :: \n", tab[i]);
        printf (" :: \n" );
    }
}

void mx_display_str(char *str)
{
    printf(" %s ++++  \n", str);
}

void mx_display_tkn(t_table tab)
{
    t_token token;
    token = tab->token; 
    if (!token)
        exit(0);
    printf("TOKEN_ID:\t%d\n", tab->token_len); // how many tkn
    printf("\nCMD== %s ==  \t", token->cmd); // 
    if (token->cmd_len > 2 )
        printf("ARG == %s == \t", token->arg);   
    printf("END_TYPE == %d == \n", token->endtype);   

}
