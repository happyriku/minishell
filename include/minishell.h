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

}	t_kind;

typedef struct s_token
{
	t_kind			kind;
	struct s_toke	*next;
	char			*metacharacter;
	char			*ctrl_op;
	char			*word;
}	t_token;

int	interpret(char *input);

#endif