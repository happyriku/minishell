#include "include/minishell.h"

extern char	**environ;
t_info g_info = {};

// void	print_error(char *input, char *name)
// {
// 	free(input);
// 	printf("%s\n", name);
// 	exit(1);
// }

char	*search_path(char *input)
{
	char	*value;
	char	*path;
	char	*pos;
	int		path_len;

	value = getenv("PATH");
	if (!value)
		return (NULL);
	while (*value)
	{
		pos = strchr(value, ':');
		if (!pos)
			path_len = strlen(value);
		else
			path_len = strlen(value) - strlen(pos);
		path = (char *)malloc(sizeof(char) * (path_len + strlen(input) + 2));
		if (!path)
			return (NULL);
		ft_strncpy(path, value, path_len);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, input, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		if (!pos)
			return (NULL);
		value = pos + 1;
	}
	return (NULL);
}

void	cleanup_token(t_token **token)
{
	t_token	*cur;
	t_token *next;

	cur = *token;
	while (cur)
	{
		next = cur->next;
		if (cur->word)
			free(cur->word);
		free(cur);
		cur = next;
	}
	*token = NULL;
}

void	setup_argv(char **argv, t_token *token)
{
	int		i;
	t_token	*tmp;

	tmp = token;
	i = 0;
	while (tmp)
	{
		argv[i] = tmp->word;
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
}

int	interpret(char *input)
{
	char	**argv;
	pid_t	pid;
	int		status;
	char	*path;
	int		i;
	t_token	*token;
	t_token *tmp;
	t_info	info;

	if (*input < 1)
		return (0);
	token = tokenize(input);
	if (!token)
		return (1);
	token = expand(token);
	if (!token)
		return (1);
	else if (g_info.syntax_error)
	{
		cleanup_token(&token);
		g_info.syntax_error = false;
		return (0);
	}
	argv = (char **)malloc(sizeof(char *) * (ft_lstsize(token) + 1));
	if (!argv)
		return (cleanup_token(&token), 1);
	setup_argv(argv, token);
	if (strncmp(argv[0], "exit", 4) == 0)
	{
		printf("exit\n");
		free(argv);
		cleanup_token(&token);
		return (EXIT);
	}
	pid = fork();
	if (pid < 0)
	{
		cleanup_token(&token);
		return (free(argv), 1);
	}
	else if (pid == 0)
	{
		path = search_path(argv[0]);
		if (!path)
		{	
			if (!strchr(argv[0], '/'))
			{
				printf("%s: command not found\n", argv[0]);
				free(argv);
				cleanup_token(&token);
				exit(0);
			}
			path = argv[0];
		}
		if (strncmp(argv[0], "echo", 4) == 0 && argv[1] != NULL)
		{
			i = 1;
			if (argv[i + 1] == NULL)
				printf("%s", argv[i]);
			else
			{
				while (argv[i] != NULL && is_word(argv[i]))
				{
					printf("%s", argv[i]);
					printf(" ");
					i++;
				}
			}
			printf("\n");
			free(argv);
			cleanup_token(&token);
			exit(0);
		}
		if (execve(path, argv, environ) == -1)
		{
			free(argv);
			cleanup_token(&token);
		}
	}
	else
	{
		wait(&status);
		free(argv);
		cleanup_token(&token);
		return (!WIFEXITED(status));
	}
	return (0);
}
