#include "../include/minishell.h"

extern char **environ;

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

void	setup_argv(char **argv, t_node *node)
{
	int		i;
	t_node	*tmp;

	tmp = node;
	i = 0;
	while (tmp)
	{
		argv[i] = tmp->args;
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
}

int	exec(t_node *node)
{
	char	**argv;
	pid_t	pid;
	char	*path;
	int		i;
	int		status;

	argv = (char **)malloc(sizeof(char *) * (ft_lstsize(node) + 1));
	if (!argv)
		return (MALLOC_ERROR);
	setup_argv(argv, node);
	if (strncmp(argv[0], "exit", 4) == 0)
	{
		printf("exit\n");
		return (free(argv), -1);
	}
	pid = fork();
	if (pid < 0)
		return (free(argv), -1);
	else if (pid == 0)
	{
		path = search_path(argv[0]);
		if (!path)
		{	
			if (!strchr(argv[0], '/'))
			{
				printf("%s: command not found\n", argv[0]);
				return (free(argv), 1);
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
			return (free(argv), 1);
		}
		if (execve(path, argv, environ) == -1)
			return (free(argv), 0);
	}
	else
	{
		wait(&status);
		free(argv);
		return (!WIFEXITED(status));
	}
	return (0);
}