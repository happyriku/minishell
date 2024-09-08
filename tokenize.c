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

	
}

t_token	*new_token(t_kind kind, t_token *cur, char c)
{
	t_token	*token;

	if (kind == TK_METACHAR)
		token->metacharacter = c;
	if (kind == TK_OPERATOR)
		token->ctrl_op = c;
	if (kind == TK_WORD)
		token->word = c;
	cur = token->next;
	return (cur);
}

t_token	*tokenize(char *input)
{
	t_token	token;
	t_token	*cur;

	token.next = NULL;
	cur = token.next;
	while (*input)
	{
		while (ft_isspace(input))
			input++;
		if (is_metacharacter(input))
			cur = new_token(TK_METACHAR, cur, input);
		else if (is_ctrlop(input))
			cur = new_token(TK_OPERATOR, cur, input);
		else if (is_word(input))
			cur = new_token(TK_WORD, cur, input);
	}
}
