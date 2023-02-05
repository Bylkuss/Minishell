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


/* Token's end type */
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

typedef struct s_token t_token;
typedef struct s_table t_table;


struct s_token		/*	 THREE-PART NODE-FORM TOKEN	ex: token[0]= "ls", "-l", "eof",	*/
{
	int 	id;			//	# command id 
	char	**cmd;		//	... cmd[id][node]
	char	*lead;		// unique cmd to find path...
	char 	*full;		// multi **str into  *str
	char 	*path;		// outfile???
	char 	*ofile;		// open file char*
	int		endtype;	// enum endtype : err, end, redir
	int 	infile;		// staring [fd] : arg/file "<" cmd 
 	int		outfile;	// resultd [fd] : arg/file ">" endtype
	int 	tk_len;	// how many node by token (min 2) ref by
	struct s_table	*table; 
};						//t_token;

struct					s_table
{
	char **envp;          //	[*str][*str] : listed copy		ENVP["PATH"]_=_["/usr/bin"]
	char ***cmds;          //	[#][*str] 	: command seq.		CMD[#_id]["ls"]
	char **node;           //	[id][*str]	: linked attrib.	NODE[#_id]["-l"]
	pid_t pid;             //	fork dup wait
	int tk_num;            // 	how many tokens ref by div_token
	int *refs;             // id token // cmd len
	struct s_token *token; //	multi_referenciels *ptr->
};                         //t_table;

//builtins
int    			builtins_handler(t_table *tab, t_token *token, int id);
// void    			builtins_handler(char *input, char **envp);
int					is_builtin(t_token *t);
// void	    		exit_builtin(char **cmd);
// cd 
int	cd(char **cmd, char **env);
// echo
int						echo(char **cmd);
// pwd
int						pwd(void);
int						ms_export(char **cmd, char **envp);
void					env(char **envp);
void					exit_builtin(char **cmd);
char					**save_old_pwd(char **envp);
int						unset(char **cmd, char **envp);
char					**edit_env(char **envp, int pos);
		
//main
char					*getprompt(t_table *tab);
//mapping
t_table					*init_token(t_table *tab);
t_table					*init_tab(t_table *tab);
//signal.c
void					handle_sigint(int sig);
char					*ms_getenv(char *var, char **envp, int n);
char					**ms_setenv(char *var, char *value, char **envp, int n);
//parsing
void 					*check_args(char *out, t_table *tab);
// init_split
char					**init_split(char *input, char *set, t_table *tab);
// div_token
int						set_endtype(t_table *tab, char *etype);
t_table					*div_token(t_table *tab, char *set);
t_token					*get_token(t_table *tab, t_token *token, int id);
//nodes
t_table					*token_alloc(t_table *tab);

//expand
char			*expand_vars(char *str, int i, int quotes[2], t_table *tab);
char			*expand_path(char *str, int i, int quotes[2], char *var);
//nodes
t_table			*token_alloc(t_table *tab);
//redir
int				get_fd(int oldfd, char *path, int flags[2]);
t_token			*get_outfile1(t_token *t, t_table *tab);
t_token			*get_outfile2(t_token *t, t_table *tab);
t_token			*get_infile1(t_token *t, t_table *tab);
t_token			*get_infile2(t_token *t, t_table *tab);
// t_token		*get_outfile1(t_token *t, int i);
// t_token		*get_outfile2(t_token *t, int i);
// t_token		*get_infile1(t_token *t, int i);
// t_token		*get_infile2(t_token *t, int i);
//heredoc
char			*get_here_str(char *str[2], size_t len, char *limit, char *warn);
int				get_here_doc(char *str[2], char *aux[2]);
//utils
void			display_tkn(t_table *tab);
void			display_one_tkn(t_token *token, int id);
void			mx_display_tab(char **tab);
void			mx_display_str(char *str);
void			display_tkn_id(t_token *t, int id);

// char			*node_check(char *input, char *meta);
// char			*type_check(char *input, char *meta);
// t_table  	*parse_args(t_table *tab);
// char   		*getprompt(t_table tab);
char			*getcmd(char **paths, char *cmd);
void    		execustom(char **out, char *full, char *args, char **envp) ;
// char    		node_trim_q(const char *s, int squote, int dquote);

// xcve.c
char			*path_join(char *path, char *bin);
int				str_ncmp(char *str1, char *str2, int n);
int				str_ichr(char *str, char c);
char			*str_ndup(char *str, unsigned int n);
char			**str_split(char *str, char sep);
// char			*getpath(t_table *tab);
// void			*getcmd(char **paths, char *cmd);

//execmd.c
void			*execmd(t_table *tab, t_token *t, int id);
void 			get_cmd(t_table *tab, t_token *t, int id);
char			*getpath(char *cmd, char **env);

//error
void	    	error_msg(char *msg, int exiit);
void			*chk_error(int err_type, char *param, int err);
void			free_cont(void *content);

//child
void			child_builtin(t_table *tab, t_token *t);
void			*born_child(t_table *tab, t_token *token, int fd[2]);
void			*chk_fork(t_table *tab, t_token *t, int id, int fd[2]);
void    		exc_fork(t_table *tab, t_token *t, int fd[2]);


#endif
