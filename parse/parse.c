#include "minishell.h"

t_node *parse(t_token *tok)
{
    return (pipeline(&tok, tok));
}