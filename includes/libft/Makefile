SRCS = ft_isascii.c ft_strlcpy.c ft_toupper.c \
		ft_atoi.c ft_isdigit.c ft_strlen.c ft_isalnum.c \
		ft_isprint.c ft_strdup.c ft_strncmp.c ft_isalpha.c\
		ft_strlcat.c ft_tolower.c ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_calloc.c ft_memmove.c ft_memcmp.c ft_strnstr.c ft_strchr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_memchr.c ft_strjoin.c \
		ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c\
		ft_split.c ft_strmapi.c ft_striteri.c ft_putendl_fd.c\
		
SRCS_BONUS =  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -c

RM = rm -f

AR = ar rcs

OBJS = $(SRCS:.c=.o)
OBJBONUS = $(SRCS_BONUS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(NAME) $(OBJS)
	$(CC) $(CFLAGS) $(SRCS_BONUS)
	$(AR) $(NAME) $(OBJBONUS)

.PHONY: all clean fclean re bonus