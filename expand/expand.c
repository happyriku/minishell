#include "../include/minishell.h"

void	append_char(char **new_word, char word)
{
	char	*memory;

	size_t	len;

	if (*new_word == NULL)
		len = 2;
	else
		len = strlen(*new_word) + 2;
	memory = (char *)malloc(sizeof(char) * (len));
	if (!memory)
		return ;
	if (*new_word == NULL)
	{
		memory[0] = word;
		memory[1] = '\0';
	}
	else
	{
		ft_strncpy(memory, *new_word, len);
		memory[len - 2] = word;
		memory[len - 1] = '\0';
		free(*new_word);
	}
	*new_word = memory;
}

void	quote_removal(t_token *token)
{
	char	*word;
	char	*new_word;

	if (token->word == NULL)
		return ;
	word = token->word;
	new_word = NULL;
	while (*word)
	{
		if (*word != SINGLEQUOTE)
			append_char(&new_word, *word);
		word++;
	}
	token->word = new_word;
	quote_removal(token->next);
}

t_token	*expand(t_token *token)
{
	char	*new_word;

	quote_removal(token);
	return (token);
}
