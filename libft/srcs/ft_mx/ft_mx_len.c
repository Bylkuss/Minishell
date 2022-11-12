#include "libft.h"

int ft_mx_len(char **mx)
{
    int i;

    i = 0;
    while(mx && mx[i])
        i++;
    return (i);
}