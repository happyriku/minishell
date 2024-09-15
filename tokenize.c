#include "include/minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_metacharacter(char c)
{
	return (strchr("|&;()<>\t\n", c));
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
	return (!is_ctrlop(str) && !is_metacharacter(*str) && !is_blank(*str));
}

t_token	*new_token(char *str, t_kind kind)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (kind == TK_EOF)
		new_token->word = NULL;
	else
		new_token->word = str;
	new_token->next = NULL;
	new_token->kind = kind;
	return (new_token);
}

char	*get_operator(char *input, char **rest)
{
	char	*op[] = {"||", "&&", "(", ")", ";;", ";&", "&", ";", "|&", "\n"};
	int		i;
	int		length;

	length = sizeof(op) / sizeof(op[0]);
	i = -1;
	while (++i < length)
	{
		if (strncmp(input, op[i], strlen(op[i])) == 0)
		{
			(*rest) += strlen(op[i]);
			return (ft_strndup(op[i], strlen(op[i])));
		}
	}
	return (NULL);
}

char	*get_metacharacter(char c, char **rest)
{
	char	*res;

	res = strchr("|&;()<>\t\n", c);
	(*rest)++;
	return (ft_strndup(res, 1));
}

char	*get_word(char *input, char **rest)
{
	int	wc;

	wc = 0;
	while (**rest && is_word(*rest))
	{
		(*rest)++;
		wc++;
	}
	return (ft_strndup(input, wc));
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
			token->next = new_token(get_operator(input, &input), TK_OPERATOR);
		else if (is_metacharacter(*input))
			token->next = new_token(get_metacharacter(*input, &input), TK_METACHAR);
		if (is_word(input))
			token->next = new_token(get_word(input, &input), TK_WORD);
		token = token->next;
	}
	token = new_token(NULL, TK_EOF);
	return (head.next);
}
