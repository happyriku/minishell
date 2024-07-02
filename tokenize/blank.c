#include "minishell.h"

bool	is_blank(char	c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	consume_blank(char **rest, char *line)
{
    while (is_blank(*line))
		line++;
	*rest = line;
}