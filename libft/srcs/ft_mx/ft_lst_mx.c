#include "libft.h"

char **ft_lst_mx(t_list *lst)
{
    char    **mx;
    t_list  *tmp;
    char    *swp;

    tmp = lst;
    mx = NULL;
    while (tmp)
    {
        swp = ft_strdup((const char *) tmp->content);
        mx = ft_mx_ext(mx, swp);
        tmp = tmp->next;
        free(swp);
    }
    return (mx);
}