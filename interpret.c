#include "include/minishell.h"

extern char **environ;

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

char	*search_path(char *input)
{
	char	*value;
	int		res;
	char	*path;
	char	*pos;
	int		path_len;

	value = getenv(input);
	if (!value)
		return (NULL);
	while (*value)
	{
		pos = strchr(value, ':');
		if (!pos)
			return (NULL);
		path_len = strlen(value) - strlen(pos);
		path = (char *)malloc(sizeof(char) * (path_len + strlen(input) + 2));
		if (!path)
			return (NULL);
		strncpy(path, value, path_len);
		sleep(1);
		printf("\nvalue : %s\n", value);
		strcat(path, "/");
		printf("path : %s\n", path);
		path = ft_strjoin(path, input);
		printf("complete path : %s\n", path);
		if (access(path, X_OK) == 0)
		{
			printf("環境変数のPATH : %s\n", path);
			return (path);
		}
		value = pos + 1;
	}
	printf("Not found Executable files\n");
	return (NULL);
}

int	interpret(char *input)
{
	char	*argv[] = {input, NULL};
	pid_t	pid;
	int		status;
	char	*path;

	pid = fork();
	if (pid < 0)
		print_error(input, "fork failed");
	else if (pid == 0)
	{
		path = search_path(input);
		if (!path)
			path = input;
		if (execve(path, argv, environ) == -1)
			print_error(input, "exec failed");
	}
	else
	{
		wait(&status);
		if (!WIFEXITED(status))
			print_error(input, "wait failed");
	}
	return (0);
}