#include "minishell.h"

t_token	*tokenize(char	*line)
{
	t_token		head;//リストのダミーの先頭を表す
	t_token		*tok; //現在のトークンを指すポインタ

	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (is_blank(*line))
			consume_blank(&line, line);
		else if (is_word(*line))
			tok = tok->next = new_token(get_word(&line, line), TK_WORD);
		else if (is_metacharacter(*line))
			tok = tok->next = new_token(get_operator(&line, line), TK_OPERATOR);
		else
			tokenize_error("unexpected character", &line, line);
	}
	tok = tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}