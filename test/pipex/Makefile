NAME = pipex

CC 		= gcc
CFLAGS 	= -g -Wall -Wextra -Werror

HEADER 	= pipex.h

SRC 	= pipex.c util.c child.c

OBJ 	= $(SRC:.c=.o)

SRCB 	= bonus.c util.c

OBJB 	= $(SRCB:c=o)

RM 		= rm -rf

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all		: $(NAME)

clean	:
	$(RM) $(OBJ) $(OBJB)

fclean	:
	$(RM) $(OBJ) $(OBJB)
	$(RM) $(NAME)

re		: fclean all

bonus: $(OBJB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJB)

.PHONY: clean fclean re bonus
