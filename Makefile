NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

LIBFT = includes/libft/libft.a

LIBFT_PATH = includes/libft/

SRCS_PATH = src/

BUILTINS = cd
PARSING = checks




SRCS_FILES = $(addsuffix .c, $(addprefix $(SRCS_PATH)builtins/, $(BUILTINS))) \
			$(addsuffix .c, $(addprefix $(SRCS_PATH)parsing/, $(checks)))



OBJS = $(SRCS_FILES:.c=.o)

all: 	$(NAME)
	@echo "BOOM 💥💥💥💥💥 $(NAME) Compiled! 💯 $(DEFAULT)"


$(NAME): $(OBJS)
	-@$(MAKE) -C $(LIBFT_PATH)
	-@$(CC) $(CFLAGS) $(LIBFT) -lcurses -lreadline -o $(NAME) 
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