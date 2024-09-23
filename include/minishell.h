#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCCESS 0
# define EXIT_FAILED 1

# define PATH_MAX 260

# define EXIT -1
# define MALLOC_ERROR "malloc error"

# define SINGLEQUOTE 39
# define DOUBLEQUOTE 34

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>

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
	int				pid;
}	t_token;

typedef struct s_info
{
	bool	syntax_error;
	
}	t_info;

extern t_info g_info;

int		interpret(char *input);
void	cleanup_token(t_token **token);

//tokenize
t_token	*tokenize(char *input);
t_token	*new_token(char *str, t_kind kind);
bool	is_word(char *str);
bool	is_blank(char c);
bool	is_metacharacter(char c);
bool	is_ctrlop(char	*str);
bool	is_word(char *str);

//expand
t_token	*expand(t_token *token);

//utils                   *minishellが完成したらlibftの方を用いる
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strncpy(char *dst, char *src, int n);
int		ft_lstsize(t_token *lst);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

#endif