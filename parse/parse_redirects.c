#include "minishell.h"

t_node  *redirect_append(t_token **rest, t_token *tok)
{
    t_node  *redirect;

    redirect = new_node(ND_REDIRECT_APPEND);
    redirect->filename = tokdup(tok->next);
    redirect->targetfd = STDOUT_FILENO;
    *rest = tok->next->next;
    return (redirect);
}

t_node  *redirect_heredoc(t_token **rest, t_token *tok)
{
    t_node  *redirect;

    redirect = new_node(ND_REDIRECT_HEREDOC);
    redirect->delimiter = tokdup(tok->next);
    if (*(redirect->delimiter->word) == SINGLE_QUOTE || *(redirect->delimiter->word) == DOUBLE_QUOTE)
        redirect->delim_quoted = true;
    redirect->targetfd = STDIN_FILENO;
    *rest = tok->next->next;
    return (redirect);
}

t_node  *redirect_in(t_token **rest, t_token *tok)
{
    t_node  *redirect;

    redirect = new_node(ND_REDIRECT_IN);
    redirect->filename = tokdup(tok->next);
    redirect->targetfd = STDIN_FILENO;
    *rest = tok->next->next;
    return (redirect);
}

t_node  *redirect_out(t_token **rest, t_token *tok)
{
    t_node  *redirect;

    redirect = new_node(ND_REDIRECT_OUT);
    redirect->filename = tokdup(tok->next);
    redirect->targetfd = STDOUT_FILENO;
    *rest = tok->next->next;
    return (redirect);
}

