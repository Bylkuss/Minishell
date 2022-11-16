/// tranfer GNL into folder instead of libft!!!

#include "../incs/minishell.h"

extern int g_status;

- - - - - -

static void update_output(char **mx, int fd) {
    char **aux;
    char *tmp;
    char *line;

    aux = NULL;
    line = NULL;
    while(1)
    {
        line = get_next_line(fd);                           ++
        if(!line)
            break;
        tmp = ft_strlen(line, "\n");                        --
        free(line);
        aux = ft_mx_ext(aux, tmp);                          --
        free(tmp);
    }
    ft_mx_free(mx);
    *mx = aux; 
}

void    exec_custom(char **out, char *full, char *args, char **envp) {
    pid_t   pid;
    int     fd[2];
    char    **mx;

    pipe(fd);                                               --
    pid = fork();                                           --
    if(!pid)
    {
        close(fd[READ_END]);
        mx = ft_split(args, ' ');                           --
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]);
        if(!access(full, F_OK))
            execve(full, mx, envp);
        exit(1);
    }
    close(fd[WRITE_END]);
    waitpid(pid, NULL, 0);
    update_output(out, fd[READ_END]);                       ++ ()
    close(fd[READ_END]); 
}

- - - - - - 
{
    static char *get_home(t_prompt prompt){
        char *tmp;
        char *pwd;
        char *home;

        pwd = getcwd(NULL, 0);                                          --
        if (!pwd)
            pwd = ft_strdup("@ ");
        home = mini_getenv("HOME", prompt.env, 4);
        if (homme && home[0] && ft_strnstr(pwd, home,ft_strlen(pwd)))   --
        {
            tmp = pwd;
            pwd = ft_strjoin("-", &pwd[ft_strlen(home)]);
            free(tmp);
        }
        free(home);
        home = ft_strjoin(BLUE, pwd);
        free(pwd);
        pwd = ft_strjoin(home, " ");
        free(home);
        return(pwd); 
    }

    static char *get_user(t_prompt prompt) {
        char **user;
        char *tmp;
        char *tmp2;

        user = NULL;
        tmp2 = NULL;
        exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);   ++ (F)
        if (!user)
            user = ft_mx_ext(user, "guest");                            --
        if (!ft_strcmp(user[0], "root", 4))
            tmp2 = ft_strjoin(NULL, RED);
        else if ((int)(user[0][0]) % 5 == 0)
            tmp2 = ft_strjoin(NULL, CYAN);
        else if ((int)(user[0][0]) % 5 == 1)
            tmp2 = ft_strjoin(NULL, GRAY);
        else if ((int)(user[0][0]) % 5 == 2)
            tmp2 = ft_strjoin(NULL, GREEN);
        else if ((int)(user[0][0]) % 5 == 3)
            tmp2 = ft_strjoin(NULL, MAGENTA);
        else 
            tmp2 = ft_strjoin(NULL, YELLOW);
        tmp = ft_strjoin(tmp2, *user);
        free(tmp2);
        ft_mx_free(&user);
        return (tmp); 
    }
}
    >> prompt.c : _getPWD, _getUSER, _default
    char    *mini_getprompt(t_prompt prompt) {
        char *tmp;
        char *tmp2;
        char *aux;

        tmp = get_user(prompt);                             ++ (E)
        tmp2 = ft_strjoin(tmp, "@mishell");
        free(tmp);
        aux = get_home(prompt);                             ++ (G)
        tmp = ft_strjoin(tmp2, aux);
        free(aux);
        free(tmp2);
        if (!g_status || g_status == -1)
            tmp2 = ft_strjoin(tmp, BLUE);
        else
            tmp2 = ft_strjoin(tmp, RED);
        free(tmp);
        tmp =ft_strjoin(tmp2, "$ ");
        free(tmp2);
        tmp2 = ft_strjoin(tmp, DEFAULT);
        free(tmp);
        return (tmp2); 
    }

- - - - - -
{
    static void mini_getpid(t_prompt *p) {
        pid_t   pid;

        pid = fork();                                               --
        if (pid < 0)
        {
            mini_perror(FORKERR, NULL, 1);                          --
            ft_mx_free(&p->envp);                                   --
            exit(1);
        }
        if (!pid)
        {
            ft_mx_free(&p->envp);                                   --
            exit(1);
        }
        waitpid(pid, NULL, 0);                                      --
        p->pid = pid - 1; 
    }

    static t_prompt init_vars(t_prompt prompt, char *str, char **av){
        char *num;

        str = getcwd(NULL, 0);                                              --
        prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);              ++ (C_1)
        free(str);
        str = mini_getenv("SHLVL", prompt.envp, 5);                         ++ (C_2)
        if(!str || ft_atoi(str) <= 0)
            num = ft_strdup("1");
        else
            num = ft_itoa(ft_atoi(str) + 1);
        free(str);
        prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);            ++ (C_1)
        free(num);
        str = mini_getenv("PATH", prompt.envp, 4);                          ++ (C_2)
        if(!str)
            prompt.envp = mini_setenv("PATH", \
            "/usr/local/sbin/:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4); ++ (C_1)
        free(str);
        str = mini_getenv("_", prompt.envp, 1);                             ++ (C_2)
        if (!str)
            prompt.envp = mini_setenv("_", av[0], prompt.envp, 1);          ++ (C_1)
        free(str);
        return (prompt); 
    }

    static t_prompt init_prompt(char **av, char **envp) {
        t_prompt prompt;
        char *str;

        str = NULL;
        prompt.cmds = NULL;
        prompt.envp = ft_mx_dup(envp);                                  --
        g_status = 0;
        mini_getpid(&prompt);                               ++  (B)
        prompt = init_vars(prompt, str, av);                ++  (C)
        return (prompt); 
    }
}
    >> check.c : prompt, signal, readline, check_args
    int main(inr ac, char **av, char **envp) {
        char *str;
        char *out;
        t_prompt prompt;

        prompt = init_prompt(av, envp);                     ++  (A)
        while (av && ac) {
            signal(SIGINT, handle_sigint);                  --
            signal(SIGQUIT, SIG_IGN);                       --
            str = mini_getprompt(prompt);                   ++  (D)
            if (str)
                out = readline(str);                        ++
            else
                out = readline("guest@minishell $ ");       ++
            free(str);
            if (!check_args(out, &prompt))                  ++ (H)
                break;
        }
        exit(g_status); 
    }
