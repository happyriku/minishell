#include "include/minishell.h"

bool	is_exit_command(char *input)
{
	if (strcmp(input, "exit") == 0)
	{
		printf("exit\n");
		return (true);
	}
	return (false);
}

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("\nExit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (is_exit_command(input))
			return (EXIT_SUCCESS);
		interpret(input);
	}
	return (EXIT_SUCCESS);
}