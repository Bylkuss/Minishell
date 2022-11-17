#include "../../includes/minishell.h"


void mx_display_tab(char **tab)
{
    int i = -1;
    if (tab[i])// && tab[0])
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

void mx_display_tkn(t_token *token)
{
    printf("\n %s ==  \n", token->cmd);
    printf("%s == \n", token->arg);   

}

t_token *init_token(t_dot *p)
{
    t_token *token = NULL;
    token->table = p->envp;
    token->cmd = p->cmds->content;
    token->arg = p->cmds->next->content;
    token->endtype = DEAD_END;

    return (token);   
}