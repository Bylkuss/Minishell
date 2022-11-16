
NAME 	=	minishell

CC 		= 	gcc
CFLAGS 	=	-Wall -Wextra -Werror ${HEADER}
RM 		=	rm -rf

FSRC	=	
F_DIR 	= 	libft/
F_PTH	= 	$(addprefix $(F_DIR), $(FSRC))
O_DIR 	= 	libft/objs/
LIBFT	= 	libft/libft.a

H_SRC 	=	minishell.h 
H_DIR	= 	includes/
H_PTH	=	$(addprefix $(H_DIR), $(H_SRC))

SRCS 	=	check.c signal.c parse.c prompt.c \
			subsplit.c divide.c update.c nodes.c \
			expand.c trimm_all.c redir.c \
			get_next_line.c get_next_line_utils.c 
S_DIR	= 	srcs/
S_PTH	= 	$(addprefix $(S_DIR), $(SRCS))
OBJ_S 	=	$(S_PTH:.c=.o)

RDPATH = readline/libreadline.a readline/libhistory.a

<<<<<<< HEAD
BUILTINS = cd
PARSING = 
=======
$(NAME): 	$(OBJ_S)
	-@$(MAKE) -C $(F_DIR) 
	-@$(CC) $(CFLAGS) $(OBJ_S) $(LIBFT) $(RDPATH) -lcurses -lreadline -o $(NAME) 

all		:	$(NAME)

clean	:
				$(RM) $(OBJ_F) 
				$(RM) $(OBJ_S) 
				
fclean	:	clean
				$(RM) $(O_DIR)
				$(RM) $(NAME)
>>>>>>> 89f56f90562a37e480241920f90b194aa06a640f

re		:	fclean all

<<<<<<< HEAD
SRCS_FILES = $(addsuffix .c, $(addprefix $(SRCS_PATH)builtins/, $(BUILTINS))) \
				$(addsuffix .c, $(addprefix $(SRCS_PATH)parsing/, $(PARSING)))



OBJS = $(SRCS_FILES:.c=.o)

all: 	$(NAME)
	@echo "BOOM 💥💥💥💥💥 $(NAME) Compiled! 💯 $(DEFAULT)"


$(NAME): $(OBJS)
	-@$(MAKE) -C $(LIBFT_PATH)
	-@$(CC) $(CFLAGS) $(LIBFT)  -o $(NAME) -lcurses -lreadline
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"


clean:
			-@$(RM) $(OBJS)

fclean:		clean
			-@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re



#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
COMMIT = $(shell date "+%d %B %T")
=======
.PHONY	:	clean fclean re bonus
>>>>>>> 89f56f90562a37e480241920f90b194aa06a640f
