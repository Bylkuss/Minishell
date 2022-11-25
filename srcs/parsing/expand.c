
#include "../../includes/minishell.h"

extern int g_status;

static char *get_substr_var(char *str, int i, t_dot *p)
{
    char *aux;
    int pos;
    char *path;
    char *var;

    pos = ft_strchar_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
    if (pos == -1)
        pos = ft_strlen(str) - 1;
    aux = ft_substr(str, 0, i - 1);
    var = ms_getenv(&str[i], p->envp, \
        ft_strchar_i(&str[i], "\"\'$|>< "));
    if (!var && str[i] == '$')
        var = ft_itoa(p->pid);
    else if (!var && str[i] == '?')
        var = ft_itoa(g_status);
    path = ft_strjoin(aux, var);
    free(aux);
    aux = ft_strjoin(path, &str[i + pos]);
    free(var);
    free(path);
    free(str);
    return (aux);
}

char    *expand_path(char *str, int i, int quotes[2], char *var)
{
    char *path;
    char *aux;

    quotes[0] = 0;
    quotes[1] = 0;
    while (str && str[++i])
    {
        quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
        quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2; 
        if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0 || \
            str[i - 1] != '$'))
        {
            aux = ft_substr(str, 0, i);
            path = ft_strjoin(aux, var);
            free(aux);
            aux = ft_substr(str, i - 1, ft_strlen(str));
            free(str);
            str = ft_strjoin(path, aux);
            free(aux);
            free(path);
            return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
        }
    }
    free(var);
    return (str);
}

char    *expand_vars(char *str, int i, int quotes[2], t_dot *p)
{
    quotes[0] = 0;
    quotes[1] = 0;
    while(str && str[++i])
    {
        quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
        quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
        if (!quotes[0] && str[i] == '$' && str[i + 1] && \
            ((ft_strchar_i(&str[i + 1], "/~%^{}:; ") && !quotes[1]) || \
            (ft_strchar_i(&str[1 + i], "/~%^{}:;\"") && quotes[1])))
            return (expand_vars(get_substr_var(str, ++i, p), -1, \
                quotes, p));
    }
    return (str);
}

/*
from parse.c (split_all)
    expand_vars => check spec. char. match by get_substr_var();
    expand_path => check relativ path match
    get_substr_var => get cmd's pid and *str pos;
    *** dispatcher to be return full path cmd & str_ptr & PID ***
*/