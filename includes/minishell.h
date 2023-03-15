/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 04:36:20 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/14 20:31:51 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../includes/get_next_line.h"
# include "../libft/incs/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* fd Refs*/
# define READ_END 0
# define WRITE_END 1

/* Colors Defined*/
# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[0;90m\002"
# define RED "\001\033[0;91m\002"
# define GREEN "\001\033[0;92m\002"
# define YELLOW "\001\033[0;93m\002"
# define BLUE "\001\033[0;94m\002"
# define MAGENTA "\001\033[0;95m\002"
# define CYAN "\001\033[0;96m\002"
# define WHITE "\001\033[0;97m\002"

enum	chk_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

// extern int g_status;

typedef struct s_table /*	Main Struct  tab->*/
{
	t_list *cmdl;
	char **envp; //	[*str][*str] : listed copy
	pid_t pid;   //	fork dup wait
}		t_table;

typedef struct s_node /*		THREE-PART token-FORM node	ex: node[0]= "ls",
				"-l", "eof",	*/
{
	char **cmd;  //	token_array
	char *path;  // 	path to find exec
	int infile;  // 	fd[0] == STDIN_FILNO  <|also|>  [READ_END]
	int outfile; // 	fd[1] == STDOUT_FILNO <|also|>  [WRITE_END]
}		t_node;

///builtins
int		builtins(t_table *tab, t_list *cmd, int *is_exit);
int		is_builtin(t_node *t);
char 	*cmd_trimmed(char *envp);
char	**edit_env(char **envp, int pos);
// int					exit_builtin(char **cmd);
int		ms_exit(t_list *cmdl, int *is_exit);
// cd
int		cd(char **cmd, char **env);
// echo
int		echo(char **cmd);
// pwd
int		pwd(void);
void	env(char **envp);
// int		ms_export(char **cmd, char **envp);
char	 **ms_export(char **cmd, char **envp);
int		unset(char **cmd, char **envp);
char	**save_old_pwd(char **envp);
char	**edit_env(char **envp, int pos);
///mapping
void	handle_sigint(int sig);
char	*getprompt(t_table tab);
char	**ms_setenv(char *var, char *value, char **envp, int n);
char	*ms_getenv(char *var, char **envp, int n);
char	*q_trim(char const *s1, int squote, int dquote);
///parsing
void	*check_args(char *out, t_table *tab);
char	**init_split(const char *input, char *set); //, t_table tab);
char	**div_str(const char *s, char *set);
char	*expand_vars(char *str, int i, int quotes[2], t_table *tab);
char	*expand_path(char *str, int i, int quotes[2], char *var);
t_list	*get_node(char **tkn, int i);
///operator
int		get_fd(int oldfd, char *path, int flags[2]);
t_node	*get_outfile1(t_node *t, char **a, int *i);
t_node	*get_outfile2(t_node *t, char **a, int *i);
t_node	*get_infile1(t_node *t, char **a, int *i);
t_node	*get_infile2(t_node *t, char **a, int *i);
char	*get_here_str(char *str[2], size_t len, char *limit, char *warn);
int		get_here_doc(char *str[2], char *aux[2]);
void	*execmd(t_table *tab, t_list *cmd);
char	*getcmd(char **paths, char *cmd);
void	child_builtin(t_table *tab, t_node *t, int l, t_list *cmd);
void	*born_child(t_table *tab, t_list *cmd, int fd[2]);
void	*chk_fork(t_table *tab, t_list *cmd, int fd[2]);
void	exc_fork(t_table *tab, t_list *cmd, int fd[2]);
void	execustom(char ***out, char *full, char *args, char **envp);
//utils
void	error_msg(char *msg, int exiit);
void	error_msg(char *msg, int exiit);
void	*chk_error(int err_type, char *param, int err);
void	free_cont(void *content);
//quotes??
int		is_quoted(char *str);
void	print_skip_qt(char *s);

#endif
