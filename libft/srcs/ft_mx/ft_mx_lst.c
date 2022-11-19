#include "libft.h"

t_list *ft_mx_lst(char **mx)
{
    t_list *lst;
    int i;

    lst = NULL;
    i = -1;
    while (mx[++i])
        ft_lstadd_back(&lst, ft_lstnew(ft_strdup(mx[i])));
    return (lst);
}