
NAME 	=	minishell

CC 		= 	gcc
CFLAGS 	=	-Wall -Wextra -Werror ${HEADER}
RM 		=	rm -rf

FSRC	=	
F_DIR 	= 	libft/
F_PTH	= 	$(addprefix $(F_DIR), $(FSRC))
O_DIR 	= 	libft/objs/
LIBFT	= 	libft/libft.a

#DIR_OBJS = objs

H_SRC 	=	minishell.h 
H_DIR	= 	-I includes/
H_PTH	=	$(addprefix $(H_DIR), $(H_SRC))

SUBDIRS		=	builtins mapping operators parsing utils


SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_DIR)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_OBJS)/, $(dir)))
SRCS		= $(foreach dir, $(SRCS_DIRS), $(wildcard $(dir)/*.c))
OBJS		= $(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.c=.o))

S_DIR	= 	srcs
#S_PTH	= 	$(addprefix $(S_DIR), $(SRCS))
OBJ_S 	=	$(S_PTH:.c=.o)

RDPATH = readline/libreadline.a readline/libhistory.a

$(NAME): 	$(OBJS)
			-@$(MAKE) -C $(F_DIR) 
			-@$(CC) $(CFLAGS) $(OBJS) $(OBJ_S) $(LIBFT) $(RDPATH) -lcurses -lreadline -o $(NAME) 

$(DIR_OBJS)/%.o :	$(DIR_SRCS)/%.c
			@mkdir -p $(DIR_OBJS) $(OBJS_DIRS)
			@$(CC) $(CFLAGS) $(H_DIR) -c $< -o $@

all		:	$(NAME)

clean	:
				$(RM) $(OBJ_F) 
				$(RM) $(OBJ_S) 
				
fclean	:	clean
				$(RM) $(O_DIR)
				$(RM) $(NAME)

re		:	fclean all

<<<<<<< HEAD

$(NAME): $(OBJS)
	-@$(MAKE) -C $(LIBFT_PATH)
	-@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 
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
>>>>>>> defdeb7b1653c5fbd26b6e45e4acd53ea4a5c1ad
