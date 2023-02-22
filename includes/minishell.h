#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/get_next_line.h"
# include "../libft/incs/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

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


/* node's end type */
# define DEAD_END 0
# define PIPE_END 1
# define OUTF1_END 2
# define OUTF2_END 3
# define INF1_END  4
# define INF2_END  5
# define ERR_END   6

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

typedef struct s_node t_node;
typedef struct s_table t_table;

// struct duty change : more like a chariot, node to be fill for exec...
struct 		s_node		/*	 THREE-PART token-FORM node	ex: node[0]= "ls", "-l", "eof",	*/
{
	int 	id;			//	node_ID 
	char	**cmd;		//	token_array
	char 	*path;		// 	path to find exec
	char 	*xfile;		// 	to store redir_arg. ext.
	int		etype;		// 	etype:: pipe, redir, end
	int 	infile;		// 	fd[0] == STDIN_FILNO  <|also|>  [READ_END] 
 	int		outfile;	// 	fd[1] == STDOUT_FILNO <|also|>  [WRITE_END]
	int 	nod_len;	// 	how many token by node (min 2) ref by (TMP)
	struct 	s_table	*table; 
};	//t_node;

struct		s_table 	/*	Main Struct  tab->*/
{
	char	**envp;     //	[*str][*str] : listed copy		ENVP["PATH"]_=_["/usr/bin"]
	char	***cmds;    //	[ID][token_array] 
	char	**token;    //	token_array == input* >>> token** " ":spc_split
	t_list	*cmdl;
	int 	refs[1000];      // 	tab->refs[id] =  token[pos]; etype_flag
	int 	nods;    	// 	nombre de node total.
	pid_t 	pid;        //	fork dup wait
	struct 	s_node *node; 
};  //t_table;

//builtins
// int 	   				builtins_handler(t_table *tab, t_node *node);
// int 	   				builtins(t_table *tab, t_node *node, int *is_exit);
int					    builtins(t_table *tab, t_list *cmd, int *is_exit);
int						is_builtin(t_node *t);
// int					exit_builtin(char **cmd);
int						ms_exit(t_list *cmdl, int *is_exit);
// int					    exit_builtin(t_table *tab, int *is_exit);
	// void    			builtins_handler(char *input, char **envp);
	// int					builtins(t_table *tab, int *is_exit);
// cd 
int	cd(char **cmd, char **env);
// echo
int						echo(char **cmd);
// pwd
int						pwd(void);
int						ms_export(char **cmd, char **envp);
void					env(char **envp);
char					**save_old_pwd(char **envp);
int						unset(char **cmd, char **envp);
char					**edit_env(char **envp, int pos);
		
//main
char					*getprompt(t_table *tab);
//mapping
// t_node					*init_node(void);
// t_node					*init_node(t_table *tab);
char					*q_trim(char const *s1, int squote, int dquote);
t_table					*init_tab(t_table *tab);
t_table					*node_alloc(t_table *tab);
//signal.c
void					handle_sigint(int sig);
char					*ms_getenv(char *var, char **envp, int n);
char					**ms_setenv(char *var, char *value, char **envp, int n);
//parsing
void 					*check_args(char *out, t_table *tab);
// init_split
char					**init_split(char *input, char *set);//, t_table *tab);
// div_node
// int						set_etype(t_table *tab, char *etype);
// t_list					*get_node(t_table *tab, t_node *node, int id);
t_list					*get_node(char **tkn, int i);
// t_table					*div_node(t_table *tab, char *set);
char					**div_str(const char *s, char *set);

//expand
char			*expand_vars(char *str, int i, int quotes[2], t_table *tab);
char			*expand_path(char *str, int i, int quotes[2], char *var);
//redir
int				get_fd(int oldfd, char *path, int flags[2]);
t_node			*get_outfile1(t_node *t, char **a,int *i);
t_node			*get_outfile2(t_node *t, char **a, int *i);
t_node			*get_infile1(t_node *t, char **a, int *i);
t_node			*get_infile2(t_node *t, char **a, int *i);
// t_node			*get_outfile1(t_node *t, t_table *tab, char **a,int *i);
// t_node			*get_outfile2(t_node *t, t_table *tab, char **a, int *i);
// t_node			*get_infile1(t_node *t, t_table *tab, char **a, int *i);
// t_node			*get_infile2(t_node *t, t_table *tab, char **a, int *i);
//heredoc
char			*get_here_str(char *str[2], size_t len, char *limit, char *warn);
int				get_here_doc(char *str[2], char *aux[2]);
//utils
void			display_tkn(t_table *tab);
void			display_one_tkn(t_node *node, int id);
void			mx_display_tab(char **tab);
void			mx_display_str(char *str);
void			display_tkn_id(t_node *t, int id);

// char			*token_check(char *input, char *meta);
// char			*type_check(char *input, char *meta);
// t_table  	*parse_args(t_table *tab);
// char   		*getprompt(t_table tab);
char			*getcmd(char **paths, char *cmd);
void    		execustom(char ***out, char *full, char *args, char **envp) ;
// char    		token_trim_q(const char *s, int squote, int dquote);

// xcve.c
char			*path_join(char *path, char *bin);
int				str_ncmp(char *str1, char *str2, int n);
int				str_ichr(char *str, char c);
char			*str_ndup(char *str, unsigned int n);
char			**str_split(char *str, char sep);
// char			*getpath(t_table *tab);
// void			*getcmd(char **paths, char *cmd);

//execmd.c
void			*execmd(t_table *tab, t_list *cmd);
// void 			get_cmd(t_table *tab, t_list *cmd);
void		 	get_cmd(t_table *tab, t_list *cmd, char **s, char *path);
char			*getpath(char *cmd, char **env);

//error
void	    	error_msg(char *msg, int exiit);
void			*chk_error(int err_type, char *param, int err);
void			free_cont(void *content);

//child
void			child_builtin(t_table *tab, t_node *t, int l, t_list *cmd);
void			*born_child(t_table *tab, t_list *cmd, int fd[2]);
void			*chk_fork(t_table *tab, t_list *cmd, int fd[2]);
void    		exc_fork(t_table *tab, t_list *cmd, int fd[2]);


#endif
