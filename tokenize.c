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

t_token	*new_token(t_kind kind, t_token *token, char *str, char **rest)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (kind == TK_EOF)
	{
		new_token->word = NULL;
		return (token);
	}
	else if (kind == TK_METACHAR)
		new_token->word = str;
	else if (kind == TK_WORD)
	{
		while (**rest && !is_blank(**rest))
		{
			printf("*rest : %p\n", *rest);
			(*rest)++;
		}
		new_token->word = str;
	}
	return (new_token->next);
}

t_token	*tokenize(char *input)
{
	t_token	head;
	t_token	*token;

	head.next = NULL;
	token = &head.next;
	while (*input)
	{
		while (is_blank(*input))
			input++;
		if (is_ctrlop(input))
			token = new_token(TK_OPERATOR, token, input, &input);
		else if (is_metacharacter(*input))
			token = new_token(TK_METACHAR, token, input, &input);
		if (is_word(input))
		{
			token = new_token(TK_WORD, token, input, &input);
			continue ;
		}
		input++;
	}
	token = new_token(TK_EOF, token, input, &input);
	return (head.next);
}
