#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include "../includes/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
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

/* Token's end type */
enum EndType{
	DEAD_END  = 0,
	PIPE_END  = 1,
	OUTF1_END = 2,
	OUTF2_END = 3,
	INF1_END  = 4,
	INF2_END  = 5,
	ERR_END   = 6
};

typedef struct s_token t_token;
	// typedef struct s_dot t_dot;
	// typedef struct s_mini t_mini;
typedef struct s_table t_table;





struct s_token		/*	 THREE-PART NODE-FORM TOKEN	ex: token[0]= "ls", "-l", "eof",	*/
{
	int 	id;			//	# command id 
	char	**cmd;		//	... cmd[id]
	char 	**path;		// relative || absolute
	int		endtype;	// enum endtype : err, end, redir
	int 	infile;		// staring [fd] : arg/file "<" cmd 
 	int		outfile;	// resultd [fd] : arg/file ">" endtype
	int 	tk_len;	// how many node by token (min 2) ref by
	struct s_table	*table; 
};						//t_token;





struct s_table
{
	char 	**envp;	//	[*str][*str] : listed copy		ENVP["PATH"]_=_["/usr/bin"]
	char 	**cmds;	//	[#][*str] 	: command seq.		CMD[#_id]["ls"]	
	char 	**node;	//	[id][*str]	: linked attrib.	NODE[#_id]["-l"]
	pid_t	pid;	//	fork dup wait 
	int 	tk_num;	// 	how many tokens ref by div_token
	struct s_token	*token;	//	multi_referenciels *ptr->
};					//t_table;


// struct s_dot		/*  ENVP BUILDER */  t_table
	// {
	// 	char 	**cmds;
	// 	char 	**envp;
	// 	pid_t	pid;
	// 	t_token token;
	// };
	// struct s_mini 	 	/*	MATRIX COMMAND TABLE */  repl token
	// {
	// 	char **t_cmd;
	// 	char *path;
	// 	int infile;
	// 	int outfile;
	// };
//

//builtins
// cd 
void    cd(char **cmd, char **env);
// echo
void    echo(char **cmd);
// pwd
void	pwd(void);
//mapping
void    	handle_sigint(int sig);
char		*ms_getenv(char *var, char **envp, int n);
char		**ms_setenv(char *var, char *value, char **envp, int n);

char 		**space_split(const char *s, char *set);
// char   		*getprompt(t_table tab);
// void    	exec_custom(char ***out, char *full, char *args, char **envp) ;

//parsing
// void		*check_args(char *out, t_dot *p);
t_table		*div_token(char const *s, char *set, t_table *tab);
char    	*ft_strtrim_all(const char *s, int squote, int dquote);
char		*expand_vars(char *str, int i, int quotes[2], t_table *tab);
char		*expand_path(char *str, int i, int quotes[2], char *var);
t_table		*token_nodes(t_table *tab);
//operators
int			get_fd(int oldfd, char *path, t_token *token);
t_token		*get_outfile1(t_token *token, char **args);
t_token		*get_outfile2(t_token *token, char **args);
t_token		*get_infile1(t_token *token, char **args);
// t_token		*get_infile2(t_mini *token, char **args, int *i);
//utils
void		display_tkn(t_table *tab);
void		mx_display_tab(char **tab);
void		mx_display_str(char *str);
// t_table		*init_token(t_table *tab);

//check	new

char    	*getprompt(t_table *tab);
t_table 	*init_token(t_table *tab);
t_table 	*init_tab(t_table *tab);

// static t_token *parse_args(t_table tab);
t_table 	*check_args(char *out, t_table *tab);
t_table		*token_nodes(t_table *tab);
	//  static t_dot	init_vars(t_dot prompt, char *str, char **av);
	//  static t_dot	init_prompt(char **av, char **envp); 
	// static char **split_all(char **args, t_dot p);
	// static t_dot 	parse_args(char **args, t_dot p);
#endif
