#include "minishell.h"

bool    is_word(char c)
{
    return (c && !is_metacharacter(c)); // cがヌル文字ではない
}

char    *get_single_quote_word(char **rest, char *line)
{
    char *word;
    char *start;

    start = line;
    line++;
    while (*line && *line != SINGLE_QUOTE)
        line++;
    if (*line == '\0')
        syntax_error("unquoted single character");
    line++;
    word = strndup(start, line - start);
    if (!word)
        fatal_error("strndup");
    *rest = line;
    return (word);
}

char    *get_double_quote_word(char **rest, char *line)
{
    char *word;
    char *start;

    start = line;
    line++;
    while (*line && *line != DOUBLE_QUOTE)
        line++;
    if (*line == '\0')
        syntax_error("unquoted double character");
    line++;
    word = strndup(start, line - start);
    if (!word)
        fatal_error("strndup");
    *rest = line;
    return (word);
}

char    *get_word(char **rest, char *line)
{
    char    *word;
    char    *start;

    start = line;
    if (*line == SINGLE_QUOTE)
    {
        word = get_single_quote_word(rest, line);
    }
    else if (*line == DOUBLE_QUOTE)
    {
        word = get_double_quote_word(rest, line); 
    }
    else
        {
            start = line;
            line++;
            while (*line && !is_blank(*line) && !is_metacharacter(*line))
                line++;
            word = strndup(start, line - start);
            if (!word)
                fatal_error("strndup");
            *rest = line;
        }
    return (word);
}