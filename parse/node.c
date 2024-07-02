#include "minishell.h"

t_node  *new_node(t_node_kind kind)
{
    t_node  *new_node;

    new_node = calloc(1, sizeof(t_node));
    if (new_node == NULL)
        fatal_error("calloc");
    new_node->kind = kind;
    return (new_node);
}

void	append_node(t_node **nodes, t_token *nod)
{
	if (*nodes == NULL)
	{
		*nodes = nod;
		return ;
	}
	append_node(&((*nodes)->next), nod);
}