/*  test3 follow test2.md and so follow test.md    */
#include "../incs/minishell.h"

int g_status;
- - - - - -
- - - - - -

- - - - - -
// subsplit

static int ft_count_words(const char *s, char *c, int i[2]) {
    int     h[2];

    q[0] = 0;
    q[1] = 0;
    while (s[i[0]] != '\0')
    {
        if (!ft_strchr(c, s[i[0]]))
        {
            i[1]++;
            while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
            {
                if(!q[1] && (s[i[0]] == '\"' || s[i[0]] != '\0')) //"
                    q[1] = s[i[0]];
                q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
                q[1] *= q[0] != 0;
                i[0]++;
            }
            if (q[0])
                return (-1);
        }
        else
            i[0]++;
    }
    return (i[1]);
}

static char **ft_fill_array(char **aux, const char *s, char *set, int i[3]) {
    int     len;
    int     q[2];

    q[0] = 0;
    q[1] = 0;
    len = ft+strlen(s);
    while (s[i[0]])
    {
        while(ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
            i[0]++;
        i[1] = i[0];
        while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) & s[i[0]])
        {
            q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
            q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2; //"
            i[0]++;
        }
        if (i[1] >= len)
            aux[i[2]++] = "\0";
        else
            aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
    }
    return (aux);
}

char **ft_cmdtrim(const char *s, char *set) {
    char    **aux;
    int     nwords;
    int     i[3];
    int     count[2];

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    count[0] = 0;
    count[1] = 0;
    if (!s)
        return (NULL);
    nwords = ft_count_words(s, set, counts);
    if (nwords == -1)
        return (NULL);
    aux = malloc(sizeof(char *) * (nwods + 1));
    if (aux == NULL)
        return (NULL);
    aux = ft_fill_array(aux, s, set, i);
    aux[nwords] = NULL;
    return (aux);   
}

- - - - - -
// error

void	*mini_perror(int err_type, char *param, int err) {
	g_status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

int 	ft_atoi2(const char *nptr, long *nbr) {
	int		sign;

	sign = 1;
	*nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		*nbr = 10 * *nbr + (*nptr - '0');
		nptr++;
	}
	if (*nptr && !ft_isspace(*nptr))
		return (-1);
	*nbr *= sign;
	return (0);
}

int 	mini_exit(t_list *cmd, int *is_exit) {
	t_mini	*node;
	long	status[2];

	node = cmd->content;
	*is_exit = !cmd->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	status[1] = ft_atoi2(node->full_cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (node->full_cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	return (status[0]);
}

void	cd_error(char **str[2]) {
	DIR		*dir;

	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		mini_perror(NDIR, str[0][1], 1);
	else if (str[0][1])
		mini_perror(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

void	free_content(void *content) {
	t_mini	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

- - - - - -
// 

static int  malloc_len(const char *s) {
    int count;
    int i;
    int dquote;
    int squote;

    i = 0;
    count = 0;
    dquote = 0;
    squote = 0;
    while (s)
    {
        squote = (squote + (!dquote && s[i] == '\'')) % 2;
        dquote = (dquote + (!squote && s[i] == '\"')) % 2; //"
        if ((s[i] == '\"' && !squote) || (s[i] == '\'' && !dquote)) // "
            count++;
    }
    if (squote || dquote)
        return (count);
}

char        *ft_strtrim_all(const char *s, int squote, int dquote) {
    int     count;
    int     i[2];
    char    *trimmed;

    i[1] = -1;
    i[0] = 0;
    count = malloc_len(s);
    if (!s || count == -1)
        return (NULL);
    trimmed = malloc(sizeof(char) * (ft_strlen(s) - count + 1));
    if (!trimmed)
        return (null);
    while( s[i[0]])
    {
        squote = (squote + (!dquote && s[i[0]] == '\'')) % 2;
        dquote = (dquote + (!squote && s[i[0]] == '\"')) % 2; //" 
        if (s[i[0]]) != '\"' || squote) && (s[i[0]] != '\'' || dquote) \
            && ++i[1] >= 0)
            trimmed[i[1]] = s[i[0]]; // "
        i[0]++;
    }
    trimmed[++i[1]] = '\0';
    return (trimmed);
}

- - - - - -
// nodes 

static t_mini   *mini_init(void) {
    t_mini *mini;
    mini = malloc(sizeof(t_mini));
    if (!mini)
        return (NULL);
    mini->full_cmd = NULL;
    mini->full_path = NULL;
    mini->infile = STDIN_FILENO;
    mini->outfile = STDOUT_FILENO;
    return (mini);
}

static t_mini   *get_params(t_mini *node, char **a[2], int *i) {
    if (a[0][*i])
    {
        if(a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
            node = get_outfile2(node, a[1], i);
        else if(a[0][*i][0] == '<' && a[0][*i + 1] && \
            a[0][*i + 1][0] == '<')
            node = get_infile2(node, a[1], i);
        else if (a[0][*i][0] == '<')
            node = get_infile1(node, a[1], i);
        else if (a[0][*i][0] != '|')
            node->full_cmd = ft_mx_ext(node->full_cmd, a[1][*i]);
        else 
        {
            mini_perror(PIPENDERR, NULL, 2);
            *i = -2;
        }
        return (node);
    }
    mini_perror(PIPENDERR, NULL, 2);
    *i = -2;
    return (node);
}

static char     **get_trimmed(char **args) {
    char    **tmp;
    char    *aux;
    int     i;

    i = -1;
    tmp = ft_mx_dup(args);
    while (tmp && tmp[++i])
    {
        aux = ft_strtrim_all(tmp[i], 0, 0);
        free(tmp[i]);
        tmp[i] = aux;
    }
    return (tmp);
}

static t_list   *stop_fill(t_list *cmd, char **args, char **tmp) {
    ft_lstclear(&cmd,free_content);
    ft_mx_free(&tmp);
    ft_mx_free(&args);
    return (NULL);
}

t_list      *fill_nodes(char **args, int i) {
    t_list  *cmd[2];
    char    **tmp[2];

    cmd[0] = NULL;
    tmp[1] = get_trimmed(args);
    while(args[++i])
    {
        cmd[1] = ft_lstlast(cmd[0]);
        if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
        {
            i += args[i][0] == '|';
            ft_lstaddback(&cmd[0], ft_lstnew(mini_init()));
            cmd[1] = ft_lstlast(cmd[0]);
        }
        tmp[0] = args;
        cmd[1]->content = get_params(cmd[1]->content, tmp, &i);
        if (i < 0)
            return (stop_fill(cmd[0], args, tmp[1]));
        if (!args[i])
            break;
    }
    ft_mx_free(&tmp[1]);
    ft_mx_free(&args);
    return (cmd[0]);
}
