#include "minishell.h"

bool	is_control_operator(t_token *tok)
{
	static char *const	con_opes[] = {"||", "&", "&&", ";", ";;", "(", ")",
		"|", "\n", NULL};
	size_t				i;

	i = 0;
	while (con_opes[i] != NULL)
	{
		if (strcmp(tok->word, con_opes[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	append_command_element(t_node *command, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_token(&command->args, tokdup(tok));
		tok = tok->next;
	}
	else if (strcmp(tok->word, ">>") == 0 && tok->next->kind == TK_WORD)
		append_node(&(command->redirects), redirect_append(&tok, tok));
	else if (strcmp(tok->word, "<<") == 0 && tok->next->kind == TK_WORD)
		append_node(&(command->redirects), redirect_heredoc(&tok, tok));
	else if (strcmp(tok->word, ">") == 0 && tok->next->kind == TK_WORD)
		append_node(&(command->redirects), redirect_in(&tok, tok));
	else if (strcmp(tok->word, "<") == 0 && tok->next->kind == TK_WORD)
		append_node(&(command->redirects), redirect_out(&tok, tok));
	else
		parse_error("append command element", &tok, tok);
	*rest = tok;
}

t_node  *command(t_token **rest, t_token *tok)
{
    t_node  *command;

    command = new_node(ND_COMMAND);
    command->args = new_token(NULL, TK_EOF);
    while (tok && tok->kind != TK_EOF && !is_control_operator(tok))
        append_command_element(command, &tok, tok);
    *rest = tok;
    return (command);
}