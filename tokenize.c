#include "include/minishell.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '\f' || c == '\n' || c == '\v');
}

bool	is_metacharacter(char c)
{
	return (strchr("|&;()<> \t\n", c));
}

bool	is_ctrlop(char	*str)
{
	char *op[] = {"||", "&&", "(", ")", ";;", ";&"};
	int	i;
	int	length;

	length = sizeof(op) / sizeof(op[0]);
	i = -1;
	while (++i < length)
	{
		if (strncmp(str, op, strlen(op[i])) == 0)
			return (true);
	}
	return (false);
}

bool	is_word(char *str)
{
	return (!is_ctrlop(str));
}

t_token	*word(t_token *cur, char *input, char **rest)
{
	if (is_metacharacter(*input))
		return (new_token(TK_METACHAR, cur, input));
	
}

t_token	*new_token(t_kind kind, t_token *cur, char str)
{
	if (kind == TK_EOF)
	{
		cur->word = NULL;
		return (cur);
	}
	cur->word = str;
	return (cur->next);
}

t_token	*tokenize(char *input)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head.next;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (is_ctrlop(input))
			cur = new_token(TK_OPERATOR, cur, input);
		else if(is_word(input))
			cur = word(cur, input, &input);
		input++;
	}
	cur = new_token(TK_EOF, cur, *input);
	return (head.next);
}
