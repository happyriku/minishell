#include "include/minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_metacharacter(char c)
{
	return (strchr("|&;()<>\t\n' '", c));
}

bool	is_ctrlop(char	*str)
{
	char	*op[] = {"||", "&&", "(", ")", ";;", ";&", "&", ";", "|&", "\n"};
	int		i;
	int		length;

	length = sizeof(op) / sizeof(op[0]);
	i = -1;
	while (++i < length)
	{
		if (strncmp(str, op[i], strlen(op[i])) == 0)
			return (true);
	}
	return (false);
}

bool	is_word(char *str)
{
	return (!is_ctrlop(str) && !is_metacharacter(*str));
}

t_token	*new_token(t_kind kind, char *str, char **rest)
{
	t_token	*new_token;
	size_t	wc;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	wc = 0;
	if (kind == TK_EOF)
	{
		new_token->word = NULL;
		return (new_token);
	}
	else if (kind == TK_OPERATOR)
	{	
		new_token->word = ft_strndup(str, strlen(*rest));
	}
	else if (kind == TK_METACHAR)
		new_token->word = ft_strndup(str, 1);
	else if (kind == TK_WORD)
	{
		while (**rest && is_word(*rest))
		{
			(*rest)++;
			wc++;
		}
		new_token->word = ft_strndup(str, wc);
	}
	return (new_token);
}

t_token	*tokenize(char *input)
{
	t_token	head;
	t_token	*token;

	head.next = NULL;
	token = &head;
	while (*input)
	{
		while (is_blank(*input))
			input++;
		if (is_ctrlop(input))
		{
			token->next = new_token(TK_OPERATOR, input, &input);
			input++;
		}
		else if (is_metacharacter(*input))
		{
			token->next = new_token(TK_METACHAR, input, &input);
			input++;
		}
		if (is_word(input))
			token->next = new_token(TK_WORD, input, &input);
		token = token->next;
	}
	token = new_token(TK_EOF, input, &input);
	return (head.next);
}
