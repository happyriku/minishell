#include "../include/minishell.h"

void	do_redirect(t_node *redirect, char *word)
{
	int	fd;

	fd = open(redirect->filename, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		fatal_error("open");
	write(fd, word, strlen(word));
	if (dup2(fd, STDOUT_FILENO) == -1)
		fatal_error("dup2");
	return ;
}

int	exec_echo(char **argv, t_node *node)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (node->redirect != NULL)
			do_redirect(node->redirect, argv[i]);
		else if (argv[i] && is_word(argv[i]))
		{
			printf("%s", argv[i]);
			printf(" ");
		}
	}
	printf("\n");
	return (free(argv), 1);
}
