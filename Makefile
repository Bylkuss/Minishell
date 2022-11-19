
NAME 	=	minishell

#	LIBFT
FSRC	=	
F_DIR	=	libft/
F_PTH	=	$(addprefix $(F_DIR), $(FSRC))
O_DIR 	=	libft/objs/
LIBFT	=	libft/libft.a

S_DIR	=	srcs
S_OBJ	=	objs
SUBDIRS		= builtins mapping operators parsing utils

SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_DIR)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_OBJ)/, $(dir)))
SRCS		= $(foreach dir, $(SRCS_DIRS), $(wildcard $(dir)/*.c))
OBJS		= $(subst $(S_DIR), $(S_OBJ), $(SRCS:.c=.o))

#	READLINE HEADER
RDPATH 		= readline/libreadline.a readline/libhistory.a
#	HEADER
H_DIR		= -I includes

SRCS_PATH = src/

#	BUILD FOLDER
$(S_OBJ)/%.o :	$(S_DIR)/%.c
			@mkdir -p $(S_OBJ) $(OBJS_DIRS)
			@$(CC) $(CFLAGS) $(H_DIR) -c $< -o $@

all		:	$(NAME)
			@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

$(NAME): 	$(OBJS)
		-@$(MAKE) -C $(F_DIR) 
		-@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RDPATH) -lcurses -lreadline -o $(NAME) 

clean	:
				@$(RM) $(OBJ_F) 
				@$(RM) -rf $(S_OBJ)
				@echo "$(RED)$(S_OBJ) deleted!$(DEFAULT)"
				
fclean	:	clean
				@$(RM) -rf $(O_DIR)
				@$(RM) $(NAME)
				@echo "$(RED)$(NAME) deleted!$(DEFAULT)"

re		:	fclean all

.PHONY:		all clean fclean re



#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m