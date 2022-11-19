#include "libft.h"

int ft_strchar_i(const char *s, char *set) 
{
    int     i;

    i = 0;
    if (!s)
        return (-1);
    while (s[i] != '\0')
    {
        if (ft_strchr(set, s[i]))
            return (i);
        i++;
    }
    return (-1);
}