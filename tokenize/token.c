#include "minishell.h"

t_token *new_token(char *word, t_token_kind kind)
{
    t_token *new_token;

    new_token = calloc(1, sizeof(t_token));
    if (!new_token)
        fatal_error("malloc");
    new_token->word = word;
    new_token->kind = kind;
    new_token->next = NULL;
    return (new_token);
}

t_token *tokdup(t_token *tok)
{
    t_token *new_tok;

    new_tok = calloc(1, sizeof(t_token));
    if (new_tok == NULL)
        fatal_error("calloc");
    new_tok->word = strdup(tok->word);
    if (new_tok->word == NULL)
        fatal_error("strdup");
    new_tok->kind = tok->kind;
    return (new_tok);
}

void    append_token(t_token **tokens, t_token  *tok)
{
    if (*tokens == NULL || (*tokens)->kind == TK_EOF)
    {
        *tokens = tok;
        (*tokens)->next = new_token(NULL, TK_EOF);
        return ;
    }
    append_token(&(*tokens)->next, tok);
}