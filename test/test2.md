/* test2 follow test.md */

#include "../incs/minishell.h"

int g_status;
- - - - - -
// expand

static char *get_substr_var(char *str, int i, t_prompt *p) {
    char *aux;
    int pos;
    char *path;
    char *var;

    pos = ft_strchar_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
    if (pos == -1)
        pos = ft_strlen(str) - 1;
    aux = ft_substr(str, 0, i - 1);
    var = mini_getenv(&str[i], p->envp, \
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

char    *expand_path(char *str, int i, int quotes[2], char *vars) {
    char *path;
    char *aux;

    quotes[0] = 0;
    quotes[1] = 0;
    while (str && str[++i])
    {
        quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
        quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2; // "
        if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0) || \
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

char    *expand_vars(char *str, int i, int quotes[2], t_prompt *p) {
    quotes[0] = 0;
    quotes[1] = 0;
    while(str && str[++i])
    {
        quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
        quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\*')) % 2;
        if (!quotes[0] && str[i] == '$' && str[i + 1] && \
            ((ft_strchar_i(&str[i + 1], "/~%^{}:; ") && !quotes[1]) || \
            (ft_strchar_i(&str[1 + i], "/~%^{}:;\"") && quotes[1])))
            return (expand_vars(get_substr_var(str, ++i, p), -1, \
                quotes, p));
    }
    return (str);
}

- - - - - - 
// args

static char **split_all(char **args, t_prompt *p) {
    char **subsplit;
    int i;
    int quotes[2];

    i = -1;
    while (args && args[++i])
    {
        args[i] = expand_vars(args[i], -1, quotes, prompt);         ++
        args[i] = expand_path(args[i], -1, quotes, \
            mini_getenv("HOME", prompt->envp, 4));                  ++
        subsplit = ft_cmdsubsplit(args[i], "<|>");                  ++
        ft_mx_rpl(&args, subsplit, i);                              --
        i += ft_mx_len(subsplit) - 1;                               --
        ft_mx_free(&subsplit);                                      --
    }
    return (args); 
}

static void *parse_args(char **args, t_prompt *p) {
    int is_exit;
    int i;

    is_exit = 0;
    p->cmds = fill_nodes(split_all(args, p), -1);               ++  ++
    if (!p->cmds)
        return (p);
    i = ft_lstsize(p->cmds);
    g_status = builtin(p, p->cmds, &is_exit, 0);                ++
    while (i-- > 0)
        waitpid(-1, &g_status, 0);
    if (!is_exit && &g_status == 13)
        g_status = 0;
    if (g_status > 255)
        g_status = g_status / 255;
    if (args && is_exit)
    {
        ft_lstclear(&p->cmds, free_content);
        return (NULL);
    }
    return (p);
}

void    *check_args(char *out, t_prompt *p) {
    char    **a;
    t_mini  *n;

    if (!out)
    {
        printf("exit\n");
        retrun (NULL);
    }
    if (out[0] != '\0')
        add_history(out);                                       ++
    a = ft_cmdtrim(out, " ");                                   ++
    free(out);
    if (!a)
        return ("");
    p = parse_args(a, p);                                       ++
    if (p && p->cmds)
        n = p->cmds->content;
    if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
        p->envp = mini_setenv("_", n->full_cms[ft_mx_len(n->full_cmd) - 1], \
            p->envp, 1);                                         --
    if (p && p->cmds)
        ft_lstclear(&p->cmds, free_content);
    return (p); 
}
- - - - - -


char    **ft_cmd_div(char const *s, char *set)
{
    char    **aux;
    int     wnum;
    int     i[3];

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    if (!s)
        return (NULL):
    wnum = word_count((char *)s, set, 0);
    if (wnum == -1)
        return (NULL);
    aux = malloc(sizeof(char *) * (wnum + 1)) ;
    if (aux == NULL)
        return (NULL);
    aux = ft_fill_array(aux, (char *)s, set, i);
    aux[wnum] = NULL;
    return (aux);    
}

- - - - - - 
// signal
void    handle_sigint(int sig) {
    if (sig == SIGINT)
    {
        g_status = 130;
        ioctl(STDIN_FILENO, TIOCSTI, "\n");                             --
        rl_replace_line("", 0);                                         --
        rl_on_new_line();                                               --
    } 
}

- - - - - - 
// (C_1)
char    *mini_getenv(char *var, char **envp, int n) {
    int i;
    int n2;

    i = 0;
    if (n < 0)
        n = ft_strlen(var);
    while (!ft_strchr(var, '-') && envp && envp[i])
    {
        n2 = n;
        if (n2 < ft_strchr_i(envp[i], '='))                          //   --
            n2 = ft_strchr_i(envp[i], '=');                           //  --
        if(!ft_strncmp(envp[i], var, n2))
            return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
        i++;
    }
    return (NULL);  
}

// (C_2)
char    **mini_setenv(char *var, char *value, char **envp, int n) {
    int i[2];
    char *aux[2];

    if (n < 0)
        n = ft_strlen(var);
    i[0] = -1;
    aux[0] = ft_strjoin(var, "=");
    aux[1] = ft_strjoin(aux[0], value);
    free(aux[0]);
    while (!ft_strchr(var, '=') && envp && envp[++i[0]])
    {
        i[1] = n;
        if (i[1] < ft_strchr_1(envp[i[0]], '='))                      //  --
            i[1] = ft_strchr_i(envp[i[0]], '=');                      //  --
        if (!ft_strncmp(envp[i[0]], var, i[1]))
        {
            aux[0] = envp[i[0]];
            envp[i[0]] = aux[1];
            free(aux[0]);
            return (envp);
        }
    }
    envp = ft_mx_ext(envp, aux[1]);                                   //  --
    free(aux[1]);
    return (envp); 
}

