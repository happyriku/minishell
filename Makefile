NAME = minishell

SRCS = main.c \
		interpret.c \
		tokenize/tokenize.c \
		tokenize/new_token.c \
		tokenize/validation.c \
		
OBJS = $(SRCS:.c=.o)

LIBS = -lreadline
CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

.c.o:
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re test