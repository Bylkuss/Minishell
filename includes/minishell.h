#ifndef MINISHELL_H
# define MINISHELL_H


# include "../libft/incs/libft.h"
# include "../includes/get_next_line.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

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

/* Token type Define*/
enum TokenType{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_SQUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_SPACE = ' ',
	CHAR_ESCAPESEQ = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	TOKEN = -1,
};

<<<<<<< HEAD
typedef struct s_prompt t_prompt;
typedef struct s_token t_token;
typedef struct s_lexer t_lexer; 
typedef struct s_mini t_mini;

struct s_prompt
{
	char *cmds;
=======
/* Token's end type */
enum EndType{
	ERR_END   = 0,
	OUTF1_END = 1,
	OUTF2_END = 2,
	INF1_END  = 3,
	INF2_END  = 4,
	PIPE_END  = 5,
	DEAD_END  = 6
};

typedef struct s_dot t_dot;
typedef struct s_mini t_mini;
typedef struct s_token t_token;
// typedef struct s_lexer t_lexer; 

struct s_dot		/*  ENVP BUILDER */
{
	t_list *cmds;
>>>>>>> 89f56f90562a37e480241920f90b194aa06a640f
	char **envp;
	pid_t	pid;
};

<<<<<<< HEAD
struct s_token
{
	char *data;
	int type;
	t_token *next;
};


struct s_lexer
{
	t_token *listok;
	int  ntok;
};

struct s_mini
=======
struct s_mini 	 	/*	MATRIX COMMAND TABLE */
>>>>>>> 89f56f90562a37e480241920f90b194aa06a640f
{
	char **full_cmd;
	char *full_path;
	int infile;
	int outfile;
};
<<<<<<< HEAD
=======

struct s_token		/*	 THREE-PART NODE-FORM TOKEN		*/
{
	char *cmd;
	char *arg;
	int	endtype;
	t_token *next;
};

//signal
void    	handle_sigint(int sig);
char	*ms_getenv(char *var, char **envp, int n);
char	**ms_setenv(char *var, char *value, char **envp, int n);
// //prompt 
char   	*getprompt(t_dot p);
//parse
void	*check_args(char *out, t_dot *p);
//subsplit
char 	**ft_cmdtrim(const char *s, char *set);
//divide
char	**ft_cmd_div(char const *s, char *set);
//update
void    exec_custom(char ***out, char *full, char *args, char **envp) ;
//expand
char	*expand_vars(char *str, int i, int quotes[2], t_dot *p);
char	*expand_path(char *str, int i, int quotes[2], char *var);
//nodes
t_list	*fill_nodes(char **args, int i);
//redir
t_mini *get_outfile1(t_mini *token, char **args, int *i);
t_mini *get_outfile2(t_mini *token, char **args, int *i);
t_mini *get_infile1(t_mini *token, char **args, int *i);
// t_mini *get_infile2(t_mini *token, char **args, int *i);
int	get_fd(int oldfd, char *path, int flags[2]);
//trimm_all
char        *ft_strtrim_all(const char *s, int squote, int dquote);
//display
void display_form(t_mini *mx);
>>>>>>> 89f56f90562a37e480241920f90b194aa06a640f


#endif
