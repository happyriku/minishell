#############
# Variables #
#############

NAME     = minishell
CC       = cc
RLDIR    = $(shell brew --prefix readline)
INCLUDES = -I include -I$(RLDIR)/include
CFLAGS   = $(INCLUDES)
LIBS     = -lreadline -L$(RLDIR)/lib
SRCS     = main.c \
		builtin/builtin_cd.c \
		builtin/builtin_echo.c \
		builtin/builtin_env.c \
		builtin/builtin_exit.c \
		builtin/builtin_export.c \
		builtin/builtin_pwd.c \
		builtin/builtin_unset.c \
		builtin/builtin.c \
		environ/environ.c \
		environ/env_init.c \
		environ/map_set.c \
		environ/map.c \
		error/error_exit.c \
		error/syntax_error.c \
		error/tokenize_error.c \
		error/parse_error.c \
		exec/exec.c \
		exec/search_path.c \
		tokenize/blank.c \
		tokenize/operator.c \
		tokenize/token.c \
		tokenize/tokenize.c \
		tokenize/word.c \
		expand/expand_env_var.c \
		expand/expand_exit_var.c \
		expand/expand_node.c \
		expand/expand_tok.c \
		expand/expand.c \
		expand/expand_heredoc_line.c \
		parse/node.c \
		parse/parse_command.c \
		parse/parse_pipeline.c \
		parse/parse_redirects.c \
		parse/parse.c \
		pipe/pipe.c \
		redirect/get_heredoc_inpipefd.c \
		redirect/redirect_open.c \
		redirect/redirect.c \
		signal/signal_handle.c \
		signal/signal.c \
		free/free.c \

OBJS     = $(SRCS:%.c=%.o)

#################
# General rules #
#################

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	./test.sh
.PHONY: all clean fclean re test

##########################
# Platform Compatibility #
##########################

# Linux | Darwin
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	# commands for Linux
endif

ifeq ($(OS),Darwin)
	# commands for macos
	RLDIR = $(shell brew --prefix readline)
	INCLUDES += -I$(RLDIR)/include
	LIBS     += -L$(RLDIR)/lib
endif
