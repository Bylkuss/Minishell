
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
			expand.c trimm_all.c redir.c display.c \
			get_next_line.c get_next_line_utils.c 
S_DIR	= 	srcs/
S_PTH	= 	$(addprefix $(S_DIR), $(SRCS))
OBJ_S 	=	$(S_PTH:.c=.o)

RDPATH = readline/libreadline.a readline/libhistory.a

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

re		:	fclean all

.PHONY	:	clean fclean re bonus
