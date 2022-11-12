#include "libft.h"

void ft_mx_free(char ***mx)
{
    int i;

    i = 0;
    while(mx && mx[0] && mx[0][i])
    {
        free(mx[0][i]);
        i++;
    }
    if (mx)
    {
        free(mx[0]);
        *mx = NULL;
    }
}