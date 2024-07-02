/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:28:10 by kkodaira          #+#    #+#             */
/*   Updated: 2024/06/30 16:35:33 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define TOKENIZE_ERROR 258
# define PARSE_ERROR 258
# define EXPORTED 1
# define UNEXPORTED 0
# define OPEN_FILES_ERROR 1

typedef enum e_token_kind{
	TK_WORD,
	TK_OPERATOR,
	TK_EOF,
}t_token_kind;

typedef struct s_token{
	char			*word;
	struct s_token	*next;
	t_token_kind	kind;
}t_token;

typedef enum e_node_kind{
	ND_PIPELINE,
	ND_COMMAND,
	ND_REDIRECT_OUT,
	ND_REDIRECT_IN,
	ND_REDIRECT_APPEND,
	ND_REDIRECT_HEREDOC,
	ND_EOF,
}t_node_kind;

typedef struct s_node{
	t_node_kind		kind;
	struct s_node	*next;
	//command
	struct s_node	*command;
	t_token			*args;
	//redirect
	struct s_node	*redirects;
	int				targetfd;
	int				stashed_targetfd;
	t_token			*filename;
	int				filefd;
	t_token			*delimiter;
	bool			delim_quoted;
	//pipeline
	int				inpipe[2];
	int				outpipe[2];
}t_node;

typedef struct s_envvar{
	char			*name;
	char			*value;
	bool			is_exported;
	struct s_envvar	*next;
}t_envvar;

typedef struct s_envmap{
	t_envvar	envvar_dummy_head;
}t_envmap;

typedef struct s_info{
	int						last_status;
	//文法エラー
	bool					syntax_error;
	bool					readline_interrupted;
	//シグナルハンドラを安全に扱える変数
	volatile sig_atomic_t	signal;
	t_envmap				*envmap;
}t_info;

extern t_info	g_info;

//builtin
void	print_envvars(bool allow_null);
int	builtin_cd(char **argv);
int	builtin_echo(char **argv);
int	builtin_env(char **argv);
int	builtin_exit(char **argv);
int	builtin_export(char **argv);
int	builtin_pwd(char **argv);
int	builtin_unset(char **argv);
bool	is_builtin(t_node *node);
int	exec_builtin(t_node *node);
char	**make_argv_from_args(t_token *args);

//environ
void	env_init(void);
void	map_set(t_envmap *map, char *name, char *value);
void	value_update(t_envvar *envvar, char *value);
t_envvar	*new_envvar(void);
char *get_value_from_name(t_envmap *map, char *name);
void map_make(t_envmap *map, char *environ, bool allow_null_value);
void divide_to_name_value(char *environ, char **name, char **value);
t_envvar	*get_envvar_from_name(t_envmap *map, char *name);
void	map_unset(t_envmap *map, char *name);
char	*make_environ_str(char *name, char *value);
char	**get_environ(t_envmap *map);

//error
void	tokenize_error(char *msg, char **rest, char *line);
void	syntax_error(char *msg);
void	fatal_error(char *msg);
void	parse_error(char *msg, t_token **rest, t_token *tok);
void	assert_error(char *msg);
void	err_exit(const char *location, const char *msg, int status);

//exec
int	exec(t_node *node);
int	exec_nonbuiltin(t_node *node);
pid_t	exec_pipeline(t_node *node);
int	wait_pipeline(pid_t	last_pid);
char	*search_path(const char *filename);

//expand
void	append_char(char **s, char c);
void	expand(t_node *node);
void	expand_tok(t_token *tok);
void	expand_node(t_node *node);
void	expand_exit_var(char **dst, char **rest, char *word);
bool	is_exit_var(char *word);
void	expand_env_name(char **dst, char **rest, char *word);
bool	is_env_name(char *word);
bool	is_alpha_num_under(char c);
bool	is_alpha_under(char c);
char	*expand_heredoc_line(char *line);

//parse
t_node	*parse(t_token *tok);
t_node	*new_node(t_node_kind kind);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_out(t_token **rest, t_token *tok);
void	append_node(t_node **nodes, t_token *nod);
t_node	*command(t_token **rest, t_token *tok);
t_node	*pipeline(t_token **rest, t_token *tok);

//pipe
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

//redirect
int	get_heredoc_inpipefd(char *delimiter, bool delim_quoted);
int	open_files(t_node *node);
void	do_redirect(t_node *redirects);
void	reset_redirect(t_node *redirects);

//signal
void	reset_signal(void);
void	setup_signal(void);
void	handler(int signum);
void	reset_sig(int signum);
void	ignore_sig(int signum);
void	handle_sig(int signum);

//tokenize
t_token	*tokenize(char *line);
bool	is_blank(char c);
void	consume_blank(char **rest, char *line);
bool	is_metacharacter(char c);
bool	is_word(char c);
char	*get_word(char **rest, char *line);
char	*get_operator(char **rest, char *line);
t_token	*new_token(char *word, t_token_kind kind);
void	append_token(t_token **tokens, t_token *tok);
t_token	*tokdup(t_token *tok);

//free
void	free_argv(char **argv);

#endif