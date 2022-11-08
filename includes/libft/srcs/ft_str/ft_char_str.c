#include "libft.h"

char *ft_char_str(char c)
{
    char *s;

    s = malloc(2);
    if (!s)
        return (NULL);
    s[0] = c;
    s[1] = '\0';
    return (s);
}