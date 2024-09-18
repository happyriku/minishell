#include "../include/minishell.h"

void	quote_removal(char *str)
{
	if ()

}

bool	is_quote(char *token)
{
	if (!token)
		return (false);
	while (*token)
	{
		if (*token == '\'' || *token == '\"')
			return (true);
		token++;
	}
	return (false);
}

t_token	*expand(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (is_quote(tmp->word))
			quote_removal(tmp->word);
		tmp = tmp->next;
	}
	//quote_removal(token);
	return (token);
}
