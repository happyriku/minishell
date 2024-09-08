#include "include/minishell.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '\f' || c == '\n' || c == '\v');
}

bool	is_metacharacter(char c)
{
	return (strchr("<>&;", c));
}

bool	is_ctrlop(char c)
{
	char op[] = {"||", "&&", "(", ")", ";;", ";&"};
	int	i;
	int	length;

	length = sizeof(op) / sizeof(op[0]);
	i = -1;
	while (++i < length)
	{
		if (c == op[i])
			return (true);
	}
	return (false);
}

bool	is_word(char c)
{
	return (!ft_isspace(c)
		&& !is_metacharacter(c) && !is_ctrlop(c));
}

t_token	*new_token(t_kind kind, t_token *cur, char c)
{
	t_token	*token;

	if (kind == TK_EOF)
	{
		token->word = NULL;
		return (cur);
	}
	else if (kind == TK_METACHAR)
		token->metacharacter = c;
	else if (kind == TK_OPERATOR)
		token->ctrl_op = c;
	else if (kind == TK_WORD)
		token->word = c;
	cur = token->next;
	return (cur);
}

t_token	*tokenize(char *input)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = head.next;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (is_metacharacter(*input))
			cur = new_token(TK_METACHAR, cur, *input);
		else if (is_ctrlop(*input))
			cur = new_token(TK_OPERATOR, cur, *input);
		else if (is_word(*input))
			cur = new_token(TK_WORD, cur, *input);
		input++;
	}
	cur = new_token(TK_EOF, cur, *input);
	return (&head);
}
