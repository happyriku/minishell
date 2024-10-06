#include "../include/minishell.h"

void	do_redirect(t_node *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_CREAT, O_RDWR);
	if (fd < 0)
		fatal_error("open");
	if (dup2(STDOUT_FILENO, fd) == -1)
		fatal_error("dup2");
	return ;
}

int	exec_echo(char **argv, t_node *node)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		// if (node->redirect->filename != NULL)
		// {
		// 	printf("=====\n");
		// 	write(STDOUT_FILENO, argv[i], sizeof(argv[i]));
		// 	do_redirect(node->redirect);
		// }
		if (argv[i] && is_word(argv[i]))
		{
			printf("%s", argv[i]);
			printf(" ");
		}
	}
	printf("\n");
	return (free(argv), 1);
}
