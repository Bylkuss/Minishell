NAME 	=	minishell

CC 		= 	gcc
CFLAGS 	=	-Wall -Wextra -Werror
RM 		=	rm -rf

H_SRC 	=	minishell.h 
H_DIR	= 	includes/
HEADER	=	$(addprefix $(H_DIR), $(H_SRC))

SRCS 	=	main.c #check.c signal.c

#prompt.c signal.c parse.c subsplit.c check.c \
			get_next_line.c get_next_line_utils.c #main.c 
S_DIR	= 	srcs/
S_PTH	= 	$(addprefix $(S_DIR), $(SRCS))
OBJ_S 	=	$(S_PTH:.c=.o)


# SRCF	= 	
# F_DIR	=	libft/
# F_PTH	= 	$(addprefix $(F_DIR), $(SRCF))
# OBJ_F	= 	$(F_PTH:.c=.o)

F_DIR = libft/

LIBFT = libft/libft.a

O_DIR = libft/objs/

RDPATH = readline/libreadline.a readline/libhistory.a

SRCS_PATH = src/


# %.o: %.c $(HEADER) Makefile
# 				@$(CC) $(CFLAGS)  -I$(F_DIR) -I$(H_DIR) -c $< -o $@

# $(NAME)	:	$(OBJ_S)
# 				$(CC)  $(OBJ_S) -o $(NAME)  -lcurses -lreadline  libft/libft.a 

# OBJS = $(SRCS_FILES:.c=.o)

$(NAME): 	$(OBJ_S)
	-@$(MAKE) -C $(F_DIR) 
	-@$(CC) $(CFLAGS) $(OBJ_S) $(RDPATH) -lcurses -lreadline -o $(NAME) 



all		:	$(NAME)

clean	:
				$(RM) $(OBJ_F) 
				$(RM) $(OBJ_S) 
				$(RM) $(O_DIR)

fclean	:	clean
				$(RM) $(NAME)

re		:	fclean all

.PHONY	:	clean fclean re bonus

