#include "../include/minishell.h"

char	*filter_operator(char *input, char **rest)
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

char	*filter_metacharacter(char c, char **rest)
{
	char	*res;

	res = strchr("|&;()<>\t\n", c);
	(*rest)++;
	return (ft_strndup(res, 1));
}

char	*filter_word(char *input, char **rest)
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
			token->next = new_token(filter_operator(input, &input), TK_OPERATOR);
		else if (is_metacharacter(*input))
			token->next = new_token(filter_metacharacter(*input, &input), TK_METACHAR);
		else if (is_word(input))
			token->next = new_token(filter_word(input, &input), TK_WORD);
		if (!token->next)
		{
			cleanup_token(&(head.next));
			return (NULL);
		}
		token = token->next;
	}
	token->next = new_token(NULL, TK_EOF);
	if (!token->next)
	{
		cleanup_token(&(head.next));
		return (NULL);
	}
	token = token->next;
	return (head.next);
}
