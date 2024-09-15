#include "include/minishell.h"

extern char	**environ;

char	*ft_strndup(const char *s1, size_t n)
{
	char		*dest;
	int			size;
	size_t		i;

	size = strlen(s1) + 1;
	dest = (char *)malloc(size * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] && i < n)
		dest[i] = s1[i];
	dest[i] = '\0';
	return (dest);
}

void	print_error(char *input, char *name)
{
	free(input);
	printf("%s\n", name);
	exit(1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = strlen(s1);
	s2_len = strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

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
		strcat(path, "/");
		path = ft_strjoin(path, input);
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
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		free(*token);
		free((*token)->word);
		*token = tmp;
	}
}

int	ft_lstsize(t_token *lst)
{
	int size;

    if (!lst)
        return (0);
	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	interpret(char *input)
{
	char	**argv;
	pid_t	pid;
	int		status;
	char	*path;
	t_token	*token;
	t_token *tmp;

	token = tokenize(input);
	tmp = token;
	while (tmp)
	{
		printf("token->word : %s\n", tmp->word);
		tmp = tmp->next;
	}
	argv = (char **)malloc(sizeof(char *) * (ft_lstsize(token) + 1));
	if (!argv)
	{
		cleanup_token(&token);
		return (1);
	}
	tmp = token;
	int i = 0;
	while (tmp)
	{
		argv[i] = tmp->word;
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
	pid = fork();
	if (pid < 0)
	{
		i = -1;
		while (++i < ft_lstsize(token))
			free(argv[i]);
		free(argv);
		cleanup_token(&token);
		print_error(input, "fork failed");
	}
	else if (pid == 0)
	{
		path = search_path(argv[0]);
		if (!path)
		{
			if (!strchr(argv[0], '/'))
			{
				printf("%s: command not found\n", argv[0]);
				return (0);
			}
			path = argv[0];
		}
		if (strncmp(argv[0], "echo", 4) == 0)
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
			
		}
		else if (execve(path, argv, environ) == -1)
			print_error(input, "exec failed");
	}
	else
	{
		wait(&status);
		i = -1;
		while (++i < ft_lstsize(token))
			free(argv[i]);
		free(argv);
		cleanup_token(&token);
		return (!WIFEXITED(status));
	}
	return (0);
}
