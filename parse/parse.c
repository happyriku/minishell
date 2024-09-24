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

t_node	*parse(t_token *token)
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
			node->next = new_node(token->word, ND_SIMPLE_CMD);
		if (!node->next)
			return (NULL);
		node = node->next;
		token = token->next;
	}
	node->next = new_node(NULL, ND_SIMPLE_CMD);
	if (!node->next)
		return (NULL);
	node = node->next;
	return (head.next);
}