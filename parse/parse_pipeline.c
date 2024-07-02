#include "minishell.h"

t_node  *pipeline(t_token **rest, t_token *tok)
{
    t_node  *node;

    node = new_node(ND_PIPELINE);
    node->inpipe[0] = STDIN_FILENO;
    node->inpipe[1] = -1;
    node->outpipe[0] = -1;
    node->outpipe[1] = STDOUT_FILENO;
    node->command = command(&tok, tok);

}