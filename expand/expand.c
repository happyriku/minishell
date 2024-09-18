#include "../include/minishell.h"

void	quote_removal(t_token *token, t_token **rest)
{
	
}

t_token	*expand(t_token *token)
{
	quote_removal(token, &token);
	return (token);
}
