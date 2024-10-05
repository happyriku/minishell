#include "../include/minishell.h"

t_node	*new_node(char *word, t_node_kind kind)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->args = word;
	node->kind = kind;
	node->next = NULL;
	return (node);
}

void	handle_metachar_syntax_error(char	*word)
{
	if (strncmp(word, ")", 1) == 0)
		printf("bash: syntax error near unexpected token ')'\n");
	else if (strncmp(word, "&", 1) == 0)
	{
		if (strcmp(word, "&") == 0)
			printf("bash: syntax error near unexpected token '&'\n");
		else
			printf("bash: syntax error near unexpected token '&&'\n");
	}
	else if (strncmp(word, "|", 1) == 0)
	{
		if (strcmp(word, "|") == 0)
			printf("bash: syntax error near unexpected token '|'\n");
		else
			printf("bash: syntax error near unexpected token '||'\n");		
	}
	else if (strncmp(word, ";", 1) == 0)
	{
		if (strcmp(word, ";") == 0)
			printf("bash: syntax error near unexpected token ';'\n");
		else
			printf("bash: syntax error near unexpected token ';;'\n");
	}
}

t_node	*new_redirect_node(t_token *token, t_node_kind kind)
{
	t_node	*redirect;

	redirect = malloc(sizeof(t_node));
	if (!redirect)
		return (NULL);
	redirect->filename = token->next->word;
	return (redirect);
}

bool	has_redirect(t_token *token)
{
	if (strcmp(token->word, ">") == 0 && token->next->kind == TK_WORD)
		return (true);
	else if (strcmp(token->word, "<") == 0 && token->next->kind == TK_WORD)
		return (true);
	else if (strcmp(token->word, ">>") == 0 && token->next->kind == TK_WORD)
		return (true);
	else if (strcmp(token->word, "<<") == 0 && token->next->kind == TK_WORD)
		return (true);
	else
		return (false);
}

t_node	*get_node(t_token *token)
{
	t_node	*node;
	t_node head;

	head.next = NULL;
	node = &head;
	while (token)
	{
		if (token->kind == TK_EOF)
			break ;
		else if (token->kind == TK_WORD)
		{
			node->next = new_node(token->word, ND_SIMPLE_CMD);
			if (!node->next)
				return (NULL);
			node = node->next;
		}
		else if (has_redirect(token))
		{
			node->redirect = new_redirect_node(token, ND_REDIRECT);
			if (!node->redirect)
				return (NULL);
		}
		token = token->next;
	}
	node->next = new_node(NULL, ND_SIMPLE_CMD);
	if (!node->next)
		return (NULL);
	node = node->next;
	return (head.next);	
}

t_node	*parse(t_token *token)
{
	t_node	*node;

	node = get_node(token);
	return (node);
}

	// else
		// {
		// 	handle_metachar_syntax_error(token->word);
		// 	g_info.syntax_error = true;
		// }