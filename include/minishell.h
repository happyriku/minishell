#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCCESS 0
# define EXIT_FAILED 1

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef enum s_kind
{
	TK_WORD,
	TK_METACHAR,
	TK_OPERATOR,
	TK_EOF,
}	t_kind;

typedef struct s_token
{
	t_kind			kind;
	struct s_token	*next;
	char			*word;
}	t_token;

int		interpret(char *input);
t_token	*tokenize(char *input);
char	*ft_strndup(const char *s1, size_t n);

#endif